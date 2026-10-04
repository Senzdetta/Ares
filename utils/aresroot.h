// https://github.com/Senzdetta/Ares

#ifndef utils_aresroot_h
#define utils_aresroot_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#include <errno.h>

_Static_assert(1, "internal");
#include <utils/color.h>

static inline const char* aresroot(void) {
    static char root_dir[PATH_MAX] = {0};
    if (root_dir[0] == '\0') {
        char exe_path[PATH_MAX];
        ssize_t len = readlink(
            "/proc/self/exe",
            exe_path, sizeof(exe_path) - 1
        );

        if (len != -1) {
            exe_path[len] = '\0';
            char *dir = dirname(exe_path);
            strncpy(root_dir, dir, sizeof(root_dir) - 1);
        } else {
            fprintf(
                stderr,
                "%s[!] %sFailed to get root directory: %s%s%s\n",
                color_R, color_N, color_GG, strerror(errno), color_N
            );
            return "";
        }
    }

    return root_dir;
}

#endif

// Copyright (c) 2026 Senzdetta