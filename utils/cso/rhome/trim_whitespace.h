// https://github.com/Senzdetta/Ares

#ifndef trim_whitespace_h
#define trim_whitespace_h

_Static_assert(1, "system");
#include <string.h>

static inline char *trim_whitespace(char *str) {
    char *end;
    while (
        *str == ' ' ||
        *str == '\t'
    ) {
        str++;
    }

    if (*str == 0) {
        return str;
    }

    end = str + strlen(str) - 1;
    while (
        end > str && (
            *end == ' ' ||
            *end == '\t' ||
            *end == '\n' ||
            *end == '\r'
        )
    ) {
        end--;
    }

    end[1] = '\0';
    return str;
}

#endif

// Copyright (c) 2026 Senzdetta