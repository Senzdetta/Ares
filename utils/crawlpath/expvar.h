// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_expvar_h
#define utils_crawlpath_expvar_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/variable.h>
#include <utils/crawlpath/exclude_list.h>

static inline void expvar(
    const char *src,
    char *dest,
    size_t dest_size
) {
    const char *root = __aresroot__;
    if (!root || strlen(root) == 0) {
        if (dest && dest_size > 0) {
            dest[0] = '\0';
        }
        return;
    }

    char temp[MAX_PATH_LEN] = {0};
    size_t d = 0;

    for (size_t i = 0; src[i] != '\0' && d < sizeof(temp) - 1;) {
        if (src[i] == '$') {
            i++;

            int has_brace = (src[i] == '{');
            if (has_brace) {
                i++;
            }

            char varname[64] = {0};
            size_t vn = 0;

            while (
                src[i] &&
                (
                    (src[i] >= 'A' && src[i] <= 'Z') ||
                    (src[i] >= 'a' && src[i] <= 'z') ||
                    (src[i] >= '0' && src[i] <= '9') ||
                    src[i] == '_'
                )
            ) {
                if (vn < sizeof(varname) - 1) {
                    varname[vn++] = src[i];
                }
                i++;
            }

            if (has_brace && src[i] == '}') {
                i++;
            }

            char replacement[MAX_PATH_LEN] = {0};
            if (strcmp(varname, "__aresroot__") == 0) {
                snprintf(
                    replacement, sizeof(replacement),
                    "%s",
                    root
                );
            } else {
                const char *env_val = getenv(varname);
                if (env_val && *env_val) {
                    snprintf(
                        replacement, sizeof(replacement),
                        "%s",
                        env_val
                    );
                } else {
                    snprintf(
                        replacement, sizeof(replacement),
                        "%s/%s",
                        root, varname
                    );
                }
            }

            if (replacement[0] != '\0') {
                size_t rlen = strlen(replacement);
                if (d + rlen < sizeof(temp) - 1) {
                    strcpy(temp + d, replacement);
                    d += rlen;
                }
            }
        } else {
            temp[d++] = src[i++];
        }
    }

    temp[d] = '\0';
    strncpy(dest, temp, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

#endif

// Copyright (c) 2026 Senzdetta