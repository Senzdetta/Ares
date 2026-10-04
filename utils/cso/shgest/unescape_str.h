// https://github.com/Senzdetta/Ares

#ifndef UNESCAPE_STR_H
#define UNESCAPE_STR_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

static inline void unescape_str(
    char *dest,
    const char *src,
    size_t max_len
) {
    size_t i = 0, j = 0;
    while (src[i] != '\0' && j < max_len - 1) {
        if (
            src[i] == '\\' &&
            (src[i+1] == 'x' || src[i+1] == 'X') &&
            src[i+2] && src[i+3]
        ) {
            char hex[3] = { src[i+2], src[i+3], '\0' };
            dest[j++] = (char)strtol(hex, NULL, 16);
            i += 4;
        } else if (src[i] == '\\' && src[i+1] == 'e') {
            dest[j++] = '\x1b';
            i += 2;
        } else {
            dest[j++] = src[i++];
        }
    }
    dest[j] = '\0';
}

#endif

// Copyright (c) 2026 Senzdetta