// https://github.com/Senzdetta/Ares

#ifndef SCANDIR_EXECUTE_CONF_H
#define SCANDIR_EXECUTE_CONF_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <visited_dir_t.h>
#include <is_visited.h>
#include <mark_visited.h>
#include <starts_with.h>
#include <get_clean_path.h>
#include <compare_strings.h>
#include <print_file_content.h>

static inline bool scandir_execute_conf(
    const char *path,
    const char *clean_filter,
    bool show_content
) {
    char real_path[PATH_MAX];
    if (!realpath(path, real_path)) {
        return false;
    }

    struct stat st;
    if (
        stat(real_path, &st) != 0 ||
        !S_ISDIR(st.st_mode)
    ) {
        return false;
    }

    if (is_visited(st.st_dev, st.st_ino)) {
        return false;
    }
    mark_visited(st.st_dev, st.st_ino);

    char clean_p[PATH_MAX];
    get_clean_path(
        path,
        clean_p,
        sizeof(clean_p)
    );

    bool match = true;
    const char *next_filter = clean_filter;

    if (
        clean_filter &&
        strlen(clean_filter) > 0
    ) {
        if (starts_with(clean_p, clean_filter)) {
            match = true;
            next_filter = NULL;
        } else if (starts_with(clean_filter, clean_p)) {
            match = false;
            next_filter = clean_filter;
        } else if (strchr(clean_p, '/') != NULL) {
            match = false;
            next_filter = clean_filter;
        } else {
            return false;
        }
    }

    DIR *dir = opendir(real_path);
    if (!dir) return false;

    char **confs = NULL;
    size_t conf_count = 0;

    char **subdirs = NULL;
    size_t sub_count = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(
            full_path,
            sizeof(full_path),
            "%s/%s",
            real_path,
            entry->d_name
        );

        struct stat ent_st;
        if (stat(full_path, &ent_st) == 0) {
            if (S_ISREG(ent_st.st_mode)) {
                confs = realloc(
                    confs,
                    (conf_count + 1) * sizeof(char *)
                );
                confs[conf_count++] = strdup(entry->d_name);
            } else if (S_ISDIR(ent_st.st_mode)) {
                subdirs = realloc(
                    subdirs,
                    (sub_count + 1) * sizeof(char *)
                );
                subdirs[sub_count++] = strdup(full_path);
            }
        }
    }
    closedir(dir);

    bool found = false;

    if (conf_count > 0 && match) {
        qsort(
            confs,
            conf_count,
            sizeof(char *),
            compare_strings
        );

        printf(
            "%s%s:\n",
            color_N, clean_p
        );

        for (size_t i = 0; i < conf_count; i++) {
            if (show_content) {
                printf(
                    "%s› %s%s%s {\n",
                    color_R, color_GG, confs[i], color_N
                );

                char file_path[PATH_MAX];
                snprintf(
                    file_path,
                    sizeof(file_path),
                    "%s/%s",
                    real_path,
                    confs[i]
                );

                print_file_content(file_path);

                printf("}\n");
            } else {
                printf(
                    "%s› %s%s%s\n",
                    color_R, color_GG, confs[i], color_N
                );
            }
        }

        printf("\n");
        found = true;
    }

    if (sub_count > 0) {
        qsort(
            subdirs,
            sub_count,
            sizeof(char *),
            compare_strings
        );

        for (size_t i = 0; i < sub_count; i++) {
            if (
                scandir_execute_conf(
                    subdirs[i],
                    next_filter,
                    show_content
                )
            ) {
                found = true;
            }
        }
    }

    for (size_t i = 0; i < conf_count; i++) {
        free(confs[i]);
    }
    free(confs);

    for (size_t i = 0; i < sub_count; i++) {
        free(subdirs[i]);
    }
    free(subdirs);

    return found;
}

#endif

// Copyright (c) 2026 Senzdetta