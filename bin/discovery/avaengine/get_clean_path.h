// https://github.com/Senzdetta/Ares

#ifndef get_clean_path_h
#define get_clean_path_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>

_Static_assert(1, "internal");
#include <strip_slashes.h>

static inline void get_clean_path(
    const char *path,
    char *out_buf,
    size_t buf_size
) {
    if (!path || !out_buf) return;

    const char *aresroot_env = getenv("__aresroot__");
    if (aresroot_env && strlen(aresroot_env) > 0) {
        char base_path[PATH_MAX];
        snprintf(
            base_path,
            sizeof(base_path),
            "%s/init/engine",
            aresroot_env
        );
        strip_slashes(base_path);

        size_t len = strlen(base_path);
        if (strncmp(path, base_path, len) == 0) {
            const char *relative = path + len;

            while (*relative == '/') {
                relative++;
            }

            if (strlen(relative) == 0) {
                snprintf(
                    out_buf,
                    buf_size,
                    "engine"
                );
            } else {
                snprintf(
                    out_buf,
                    buf_size,
                    "%s",
                    relative
                );
            }
            return;
        }
    }
    snprintf(
        out_buf,
        buf_size,
        "%s",
        path
    );
}

#endif

// Copyright (c) 2026 Senzdetta