// https://github.com/Senzdetta/Ares

#ifndef HAS_VALID_SH_FILES_H
#define HAS_VALID_SH_FILES_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

_Static_assert(1, "internal");
#include <is_valid_sh.h>

static inline int has_valid_sh_files(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) return 0;

    struct dirent *entry;
    char path[4096];
    int found_valid = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        snprintf(
            path,
            sizeof(path),
            "%s/%s",
            dir_path,
            entry->d_name
        );

        struct stat statbuf;
        if (stat(path, &statbuf) == -1) {
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            if (has_valid_sh_files(path)) {
                found_valid = 1;
                break;
            }
        } else if (S_ISREG(statbuf.st_mode)) {
            size_t len = strlen(entry->d_name);
            if (
                len > 3 &&
                strcmp(entry->d_name + len - 3, ".sh") == 0
            ) {
                if (is_valid_sh(path)) {
                    found_valid = 1;
                    break;
                }
            }
        }
    }
    closedir(dir);
    return found_valid;
}

#endif

// Copyright (c) 2026 Senzdetta