// https://github.com/Zeronetsec/Ares

#ifndef DYNAV_BUILTIN_H
#define DYNAV_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

_Static_assert(1, "internal");
#include <ignored_list.h>
#include <load_ignored_list.h>
#include <is_ignored_folder.h>
#include <free_ignored_list.h>
#include <is_readonly.h>

static inline int dynav_builtin(WORD_LIST *list) {
    char *aresroot = get_string_value("__aresroot__");
    if (!aresroot || !*aresroot) {
        return EXECUTION_SUCCESS;
    }

    int should_lock = is_readonly(aresroot);

    IgnoredList ignored = {NULL, 0, 0};
    char *config_dir = get_string_value("__config__");

    if (config_dir && *config_dir) {
        load_ignored_list(config_dir, &ignored);
    } else {
        char fallback_config[PATH_MAX];
        snprintf(
            fallback_config,
            sizeof(fallback_config),
            "%s/config",
            aresroot
        );
        load_ignored_list(
            fallback_config,
            &ignored
        );
    }

    char base_path[PATH_MAX];
    strncpy(
        base_path,
        aresroot,
        sizeof(base_path) - 1
    );
    base_path[sizeof(base_path) - 1] = '\0';

    size_t len = strlen(base_path);
    while (len > 0 && base_path[len - 1] == '/') {
        base_path[len - 1] = '\0';
        len--;
    }

    DIR *dir = opendir(base_path);
    if (!dir) {
        free_ignored_list(&ignored);
        return EXECUTION_SUCCESS;
    }

    struct dirent *entry;
    char fullpath[PATH_MAX];
    char var_name[NAME_MAX + 10];

    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        if (is_ignored_folder(entry->d_name, &ignored)) {
            continue;
        }

        snprintf(
            fullpath,
            sizeof(fullpath),
            "%s/%s",
            base_path,
            entry->d_name
        );

        int is_dir = 0;
        #ifdef _DIRENT_HAVE_D_TYPE
            if (entry->d_type != DT_UNKNOWN) {
                is_dir = (entry->d_type == DT_DIR);
            } else
        #endif
        {
            struct stat st;
            if (
                stat(fullpath, &st) == 0 &&
                S_ISDIR(st.st_mode)
            ) {
                is_dir = 1;
            }
        }

        if (!is_dir) continue;

        char lower_name[NAME_MAX];
        strncpy(
            lower_name,
            entry->d_name,
            sizeof(lower_name) - 1
        );
        lower_name[sizeof(lower_name) - 1] = '\0';

        for (int i = 0; lower_name[i]; i++) {
            lower_name[i] = tolower(
                (unsigned char)lower_name[i]
            );
        }

        snprintf(
            var_name,
            sizeof(var_name),
            "__%s__",
            lower_name
        );

        SHELL_VAR *v = bind_variable(
            var_name,
            fullpath,
            0
        );

        if (v) {
            VSETATTR(
                v,
                att_exported
            );

            if (should_lock) {
                VSETATTR(
                    v,
                    att_readonly
                );
            }
        }
    }

    closedir(dir);
    free_ignored_list(&ignored);
    return EXECUTION_SUCCESS;
}

#endif

// Copyright (c) 2026 Zeronetsec