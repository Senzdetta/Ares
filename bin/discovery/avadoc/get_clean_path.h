// https://github.com/Senzdetta/Ares

#ifndef get_clean_path_h
#define get_clean_path_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <strip_slashes.h>

static inline void get_clean_path(
    const char *path,
    char *out_buf,
    size_t buf_size
) {
    if (!path || !out_buf) return;

    const char *data_env = getenv("__data__");
    if (data_env && strlen(data_env) > 0) {
        char base_doc_path[PATH_MAX];
        snprintf(
            base_doc_path,
            sizeof(base_doc_path),
            "%s/aresdoc",
            data_env
        );
        strip_slashes(base_doc_path);

        size_t len = strlen(base_doc_path);
        if (strncmp(path, base_doc_path, len) == 0) {
            const char *relative = path + len;

            while (*relative == '/') {
                relative++;
            }

            if (strlen(relative) == 0) {
                snprintf(
                    out_buf,
                    buf_size,
                    "aresdoc"
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