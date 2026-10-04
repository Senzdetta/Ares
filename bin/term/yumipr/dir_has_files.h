// https://github.com/Zeronetsec/Ares

#ifndef DIR_HAS_FILES_H
#define DIR_HAS_FILES_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline int dir_has_files(const char *dir_path) {
    DIR *d = opendir(dir_path);
    if (!d) return 0;

    struct dirent *dir;
    int found_file = 0;

    while ((dir = readdir(d)) != NULL) {
        if (
            strcmp(dir->d_name, ".") == 0 ||
            strcmp(dir->d_name, "..") == 0
        ) {
            continue;
        }

        char full_path[MAX_PATH];
        snprintf(
            full_path, sizeof(full_path),
            "%s/%s",
            dir_path, dir->d_name
        );

        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                if (dir_has_files(full_path)) {
                    found_file = 1;
                    break;
                }
            } else {
                found_file = 1;
                break;
            }
        }
    }

    closedir(d);
    return found_file;
}

#endif

// Copyright (c) 2026 Zeronetsec