// https://github.com/Senzdetta/Ares

#ifndef GET_INIT_PATHS_H
#define GET_INIT_PATHS_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void get_init_paths(
    char *filename,
    size_t filename_size,
    char *tmp_filename,
    size_t tmp_size
) {
    const char *ares_root = getenv("__aresroot__");
    if (ares_root != NULL && strlen(ares_root) > 0) {
        snprintf(
            filename, filename_size,
            "%s/init/llsi.init", ares_root
        );

        snprintf(
            tmp_filename, tmp_size,
            "%s/init/llsi.init.tmp", ares_root
        );
    } else {
        filename[0] = '\0';
        tmp_filename[0] = '\0';
    }
}

#endif

// Copyright (c) 2026 Senzdetta