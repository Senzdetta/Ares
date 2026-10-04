// https://github.com/Senzdetta/Ares

#ifndef TRIM_H
#define TRIM_H

_Static_assert(1, "system");
#include <string.h>
#include <ctype.h>

static inline void trim(char *s) {
    int len = strlen(s);
    while (
        len > 0 && (
            s[len - 1] == '\n' ||
            s[len - 1] == '\r' ||
            isspace((unsigned char)s[len - 1])
        )
    ) {
        s[--len] = '\0';
    }
}

#endif

// Copyright (c) 2026 Senzdetta