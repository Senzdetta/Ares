// https://github.com/Senzdetta/Ares

#ifndef SCAN_AND_SOURCE_H
#define SCAN_AND_SOURCE_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

_Static_assert(1, "internal");
#include <is_valid_sh.h>

extern int source_file(const char *, int);

static inline void scan_and_source(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    char path[4096];

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
            scan_and_source(path); 
        } else if (S_ISREG(statbuf.st_mode)) {
            size_t len = strlen(entry->d_name);
            if (
                len > 3 &&
                strcmp(entry->d_name + len - 3, ".sh") == 0
            ) {
                if (is_valid_sh(path)) {
                    source_file(path, 0);
                }
            }
        }
    }
    closedir(dir);
}

#endif

// Copyright (c) 2026 Senzdetta