// https://github.com/Senzdetta/Ares

#ifndef TRIM_WHITESPACE_H
#define TRIM_WHITESPACE_H

_Static_assert(1, "system");
#include <string.h>

static inline char *trim_whitespace(char *str) {
    while (
        *str == ' ' ||
        *str == '\t' ||
        *str == '\r' ||
        *str == '\n'
    ) {
        str++;
    }

    if (*str == 0) return str;
    char *end = str + strlen(str) - 1;
    while (
        end > str &&
        (
            *end == ' ' ||
            *end == '\t' ||
            *end == '\r' ||
            *end == '\n'
        )
    ) {
        *end = '\0';
        end--;
    }
    return str;
}

#endif

// Copyright (c) 2026 Senzdetta