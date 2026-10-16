// https://github.com/Senzdetta/Ares

#ifndef get_target_path_h
#define get_target_path_h

#include <stdio.h>
#include <stdlib.h>

#include <lib/std/c/color.h>

static inline void get_target_path(
    char *path_dest,
    size_t max_len
) {
    char *aresroot = getenv("__aresroot__");
    if (!aresroot) {
        fprintf(
            stderr,
            "%s[!] %sVariable: %s__aresroot__ %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        return;
    }

    if (aresroot) {
        snprintf(
            path_dest, max_len,
            "%s/init/llsi.init",
            aresroot
        );
    }
}

#endif

// Copyright (c) 2026 Senzdetta