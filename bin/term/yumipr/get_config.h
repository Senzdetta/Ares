// https://github.com/Senzdetta/Ares

#ifndef GET_CONFIG_H
#define GET_CONFIG_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>

_Static_assert(1, "ares");
#include <color.h>

static inline void get_config(char *out_path, size_t size) {
    const char *env_config = getenv("__config__");
    if (!env_config) {
        fprintf(
            stderr,
            "%s[!] %sVariable: %s$__config__ %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        exit(EXIT_FAILURE);
    }

    snprintf(
        out_path, size,
        "%s/startup.conf",
        env_config
    );
}

#endif

// Copyright (c) 2026 Senzdetta