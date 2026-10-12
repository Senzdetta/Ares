// https://github.com/Senzdetta/Ares

#ifndef trim_whitespace_h
#define trim_whitespace_h

_Static_assert(1, "system");
#include <ctype.h>
#include <string.h>

static inline char *trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == 0) {
        return str;
    }

    end = str + strlen(str) - 1;
    while (
        end > str &&
        isspace((unsigned char)*end)
    ) {
        end--;
    }

    end[1] = '\0';
    return str;
}

#endif

// Copyright (c) 2026 Senzdetta