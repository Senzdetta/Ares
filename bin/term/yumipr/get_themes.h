// https://github.com/Senzdetta/Ares

#ifndef get_themes_h
#define get_themes_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>

_Static_assert(1, "ares");
#include <color.h>

static inline void get_themes(char *out_path, size_t size) {
    const char *env_data = getenv("__data__");
    if (!env_data) {
        fprintf(
            stderr,
            "%s[!] %sVariable: %s$__data__ %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        exit(EXIT_FAILURE);
    }

    snprintf(
        out_path, size,
        "%s/yumipr/themes",
        env_data
    );
}

#endif

// Copyright (c) 2026 Senzdetta