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

    const char *config_env = getenv("__config__");
    if (config_env && strlen(config_env) > 0) {
        char base_conf_path[PATH_MAX];
        snprintf(
            base_conf_path,
            sizeof(base_conf_path),
            "%s",
            config_env
        );
        strip_slashes(base_conf_path);

        size_t len = strlen(base_conf_path);
        if (strncmp(path, base_conf_path, len) == 0) {
            const char *relative = path + len;

            while (*relative == '/') {
                relative++;
            }

            if (strlen(relative) == 0) {
                const char *last_slash = strrchr(
                    base_conf_path, '/'
                );

                if (last_slash) {
                    size_t pos = last_slash - base_conf_path;
                    const char *prev_slash = NULL;
                    for (
                        ssize_t i = (ssize_t)pos - 1;
                        i >= 0;
                        i--
                    ) {
                        if (base_conf_path[i] == '/') {
                            prev_slash = &base_conf_path[i];
                            break;
                        }
                    }

                    if (prev_slash) {
                        snprintf(
                            out_buf,
                            buf_size,
                            "%s",
                            prev_slash + 1
                        );
                    } else {
                        snprintf(
                            out_buf,
                            buf_size,
                            "%s",
                            base_conf_path
                        );
                    }
                } else {
                    snprintf(
                        out_buf,
                        buf_size,
                        "%s",
                        base_conf_path
                    );
                }
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