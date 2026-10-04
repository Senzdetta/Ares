// https://github.com/Zeronetsec/Ares

#ifndef HAS_DIRECT_FILES_H
#define HAS_DIRECT_FILES_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline int has_direct_files(const char *dir_path) {
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
        if (stat(full_path, &st) == 0 && !S_ISDIR(st.st_mode)) {
            found_file = 1;
            break;
        }
    }

    closedir(d);
    return found_file;
}

#endif

// Copyright (c) 2026 Zeronetsec