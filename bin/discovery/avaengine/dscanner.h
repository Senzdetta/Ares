// https://github.com/Senzdetta/Ares

#ifndef dscanner_h
#define dscanner_h

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include <color.h>
#include <active_engine.h>
#include <check_active.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline void dscanner(
    const char *base_trim,
    const char *current_dir,
    int show_active,
    const ActiveEngine *active_engines,
    int active_count
) {
    DIR *dir = opendir(current_dir);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    char subdirs[1024][MAX_PATH];
    int subdir_count = 0;

    char files[1024][MAX_PATH];
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        char full_path[MAX_PATH];
        snprintf(
            full_path, sizeof(full_path),
            "%s/%s",
            current_dir, entry->d_name
        );

        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                if (subdir_count < 1024) {
                    snprintf(
                        subdirs[subdir_count++],
                        MAX_PATH,
                        "%s",
                        full_path
                    );
                }
            } else if (S_ISREG(st.st_mode)) {
                size_t len = strlen(entry->d_name);
                if (
                    len > 4 &&
                    strcmp(
                        entry->d_name + len - 4,
                        ".shx"
                    ) == 0
                ) {
                    if (file_count < 1024) {
                        char clean_name[MAX_PATH];
                        strncpy(
                            clean_name, entry->d_name,
                            len - 4
                        );

                        clean_name[len - 4] = '\0';
                        snprintf(
                            files[file_count++],
                            MAX_PATH,
                            "%s",
                            clean_name
                        );
                    }
                }
            }
        }
    }
    closedir(dir);

    if (file_count > 0) {
        const char *rel_path = current_dir;
        if (
            strncmp(
                current_dir,
                base_trim, strlen(base_trim)
            ) == 0
        ) {
            rel_path = current_dir + strlen(base_trim);
            if (rel_path[0] == '/') {
                rel_path++;
            }
        }

        printf(
            "%s%s:\n",
            color_N, rel_path
        );

        for (int i = 0; i < file_count; i++) {
            if (
                check_active(
                    base_trim,
                    current_dir,
                    files[i],
                    show_active,
                    active_engines,
                    active_count
                )
            ) {
                printf(
                    "%s› %s%s %s(%sactive%s)%s\n",
                    color_R, color_GG, files[i],
                    color_DG, color_CC, color_DG, color_N
                );
            } else {
                printf(
                    "%s› %s%s%s\n",
                    color_R, color_GG, files[i], color_N
                );
            }
        }
        printf("\n");
    }

    for (int i = 0; i < subdir_count; i++) {
        dscanner(
            base_trim,
            subdirs[i],
            show_active,
            active_engines,
            active_count
        );
    }
}

#endif

// Copyright (c) 2026 Senzdetta