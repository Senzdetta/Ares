// https://github.com/Senzdetta/Ares

#ifndef clean_dir_contents_h
#define clean_dir_contents_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

static inline void clean_dir_contents(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    char full_path[4096];

    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        snprintf(
            full_path, sizeof(full_path),
            "%s/%s",
            path, entry->d_name
        );

        struct stat st;
        if (lstat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                clean_dir_contents(full_path);
                rmdir(full_path);
            } else {
                unlink(full_path);
            }
        }
    }

    closedir(dir);
}

#endif

// Copyright (c) 2026 Senzdetta