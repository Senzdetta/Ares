// https://github.com/Senzdetta/Ares

#ifndef EXPAND_VARS_H
#define EXPAND_VARS_H

_Static_assert(1, "system");
#include <string.h>

static inline void expand_vars(
    const char *src,
    char *dest,
    size_t dest_size
) {
    size_t d = 0;
    dest[0] = '\0';

    for (
        size_t i = 0; src[i] != '\0' &&
        d < dest_size - 1;
    ) {
        if (src[i] == '$') {
            i++;
            int has_brace = 0;
            if (src[i] == '{') {
                has_brace = 1;
                i++;
            }

            char varname[256];
            size_t vn = 0;
            while (
                src[i] != '\0' && (
                    (
                        src[i] >= 'A' &&
                        src[i] <= 'Z'
                    ) ||
                    (
                        src[i] >= 'a' &&
                        src[i] <= 'z'
                    ) ||
                    (
                        src[i] >= '0' &&
                        src[i] <= '9'
                    ) ||
                    src[i] == '_'
                )
            ) {
                if (vn < sizeof(varname) - 1) {
                    varname[vn++] = src[i];
                }
                i++;
            }
            varname[vn] = '\0';

            if (has_brace && src[i] == '}') {
                i++;
            }

            const char *val = NULL;
            if (strcmp(varname, "PREFIX") == 0) {
                val = get_string_value("PREFIX");
                if (!val || !*val) {
                    val = "/usr";
                }
            } else {
                val = get_string_value(varname);
            }

            if (val) {
                size_t vlen = strlen(val);
                if (d + vlen < dest_size - 1) {
                    strcpy(dest + d, val);
                    d += vlen;
                }
            }
        } else {
            dest[d++] = src[i++];
        }
    }
    dest[d] = '\0';
}

#endif

// Copyright (c) 2026 Senzdetta