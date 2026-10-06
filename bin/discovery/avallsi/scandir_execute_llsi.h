// https://github.com/Senzdetta/Ares

#ifndef scandir_execute_llsi_h
#define scandir_execute_llsi_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <registered_llsi_t.h>
#include <visited_dir_t.h>
#include <is_visited.h>
#include <mark_visited.h>
#include <starts_with.h>
#include <get_clean_path.h>
#include <compare_strings.h>
#include <is_path_registered.h>

static inline bool scandir_execute_llsi(
    const char *path,
    const char *clean_filter,
    bool fullscan,
    const registered_llsi_t *reg
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

    char **llsi_files = NULL;
    size_t llsi_count = 0;

    char **subdirs = NULL;
    size_t sub_count = 0;

    const char *aresroot_env = getenv("__aresroot__");
    char real_aresroot[PATH_MAX] = "";
    if (aresroot_env) {
        if (
            realpath(
                aresroot_env,
                real_aresroot
            ) == NULL
        ) {
            printf(
                "%s[!] %sRealpath failed: %s%s%s\n",
                color_R, color_N, color_GG, strerror(errno), color_N
            );
            return 1;
        }
    }

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
                char *ext = strrchr(entry->d_name, '.');
                if (ext && strcmp(ext, ".llsi") == 0) {
                    char rel_llsi_path[PATH_MAX] = "";
                    if (
                        strlen(real_aresroot) > 0 &&
                        strncmp(
                            full_path,
                            real_aresroot,
                            strlen(real_aresroot)
                        ) == 0
                    ) {
                        const char *p = full_path + strlen(
                            real_aresroot
                        );

                        while (*p == '/') {
                            p++;
                        }

                        snprintf(
                            rel_llsi_path,
                            sizeof(rel_llsi_path),
                            "%s",
                            p
                        );
                    }

                    bool registered = is_path_registered(
                        reg,
                        rel_llsi_path
                    );

                    if (fullscan || registered) {
                        llsi_files = realloc(
                            llsi_files,
                            (llsi_count + 1) * sizeof(char *)
                        );
                        llsi_files[llsi_count++] = strdup(entry->d_name);
                    }
                }
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

    if (llsi_count > 0 && match) {
        qsort(
            llsi_files,
            llsi_count,
            sizeof(char *),
            compare_strings
        );

        printf(
            "%s%s:\n",
            color_N, clean_p
        );

        for (size_t i = 0; i < llsi_count; i++) {
            char name_buf[NAME_MAX];
            snprintf(
                name_buf,
                sizeof(name_buf),
                "%s",
                llsi_files[i]
            );

            char *dot = strrchr(name_buf, '.');
            if (dot && dot != name_buf) {
                *dot = '\0';
            }

            char full_file_path[PATH_MAX];
            snprintf(
                full_file_path,
                sizeof(full_file_path),
                "%s/%s",
                real_path, llsi_files[i]
            );

            char rel_llsi_path[PATH_MAX] = "";
            if (
                strlen(real_aresroot) > 0 &&
                strncmp(
                    full_file_path,
                    real_aresroot,
                    strlen(real_aresroot)
                ) == 0
            ) {
                const char *p = full_file_path + strlen(
                    real_aresroot
                );

                while (*p == '/') {
                    p++;
                }

                snprintf(
                    rel_llsi_path,
                    sizeof(rel_llsi_path),
                    "%s",
                    p
                );
            }

            bool registered = is_path_registered(
                reg,
                rel_llsi_path
            );

            if (fullscan) {
                if (registered) {
                    printf(
                        "%s› %s%s %s(%sregistered%s)%s\n",
                        color_R, color_GG, name_buf, color_DG,
                        color_CC, color_DG, color_N
                    );
                } else {
                    printf(
                        "%s› %s%s%s\n",
                        color_R, color_GG, name_buf, color_N
                    );
                }
            } else {
                printf(
                    "%s› %s%s%s\n",
                    color_R, color_GG, name_buf, color_N
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
                scandir_execute_llsi(
                    subdirs[i],
                    next_filter,
                    fullscan,
                    reg
                )
            ) {
                found = true;
            }
        }
    }

    for (size_t i = 0; i < llsi_count; i++) {
        free(llsi_files[i]);
    }
    free(llsi_files);

    for (size_t i = 0; i < sub_count; i++) {
        free(subdirs[i]);
    }
    free(subdirs);

    return found;
}

#endif

// Copyright (c) 2026 Senzdetta