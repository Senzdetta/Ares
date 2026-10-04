// https://github.com/Senzdetta/Ares

#ifndef LSTRIP_SLASH_H
#define LSTRIP_SLASH_H

_Static_assert(1, "system");
#include <string.h>

static inline char *lstrip_slash(char *str) {
    if (!str) return NULL;
    while (*str == '/') {
        str++;
    }
    return str;
}

#endif

// Copyright (c) 2026 Senzdetta