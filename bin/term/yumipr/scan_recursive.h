// https://github.com/Senzdetta/Ares

#ifndef scan_recursive_h
#define scan_recursive_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <dir_has_files.h>
#include <has_direct_files.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline void scan_recursive(
    const char *base_path,
    const char *rel_path
) {
    char full_path[MAX_PATH];
    if (rel_path && strlen(rel_path) > 0) {
        snprintf(
            full_path, sizeof(full_path),
            "%s/%s",
            base_path, rel_path
        );
    } else {
        snprintf(
            full_path, sizeof(full_path),
            "%s",
            base_path
        );
    }

    if (!dir_has_files(full_path)) {
        return;
    }

    DIR *d = opendir(full_path);
    if (!d) return;

    int contains_files = has_direct_files(full_path);
    if (contains_files) {
        if (rel_path && strlen(rel_path) > 0) {
            printf(
                "themes/%s:\n",
                rel_path
            );
        } else {
            printf("themes:\n");
        }
    }

    struct dirent *dir;

    while ((dir = readdir(d)) != NULL) {
        if (
            strcmp(dir->d_name, ".") == 0 ||
            strcmp(dir->d_name, "..") == 0
        ) {
            continue;
        }

        char item_full_path[MAX_PATH];
        snprintf(
            item_full_path, sizeof(item_full_path),
            "%s/%s",
            full_path, dir->d_name
        );

        struct stat st;
        if (
            stat(item_full_path, &st) == 0 &&
            S_ISDIR(st.st_mode)
        ) {
            continue;
        }

        if (access(item_full_path, X_OK) != 0) {
            printf(
                "%s› %s%s %s(%snot executable%s)%s\n", 
                color_R, color_GG, dir->d_name, color_DG,
                color_WW, color_DG, color_N
            );
        } else {
            printf(
                "%s› %s%s%s\n", 
                color_R, color_GG, dir->d_name, color_N
            );
        }
    }

    rewinddir(d);

    while ((dir = readdir(d)) != NULL) {
        if (
            strcmp(dir->d_name, ".") == 0 ||
            strcmp(dir->d_name, "..") == 0
        ) {
            continue;
        }

        char sub_full_path[MAX_PATH];
        snprintf(
            sub_full_path, sizeof(sub_full_path),
            "%s/%s",
            full_path, dir->d_name
        );

        struct stat st;
        if (
            stat(sub_full_path, &st) == 0 &&
            S_ISDIR(st.st_mode)
        ) {
            if (dir_has_files(sub_full_path)) {
                char sub_rel_path[MAX_PATH];
                if (rel_path && strlen(rel_path) > 0) {
                    snprintf(
                        sub_rel_path, sizeof(sub_rel_path),
                        "%s/%s",
                        rel_path, dir->d_name
                    );
                } else {
                    snprintf(
                        sub_rel_path, sizeof(sub_rel_path),
                        "%s",
                        dir->d_name
                    );
                }

                if (contains_files) {
                    printf("\n");
                }

                scan_recursive(base_path, sub_rel_path);
            }
        }
    }
    closedir(d);
}

#endif

// Copyright (c) 2026 Senzdetta