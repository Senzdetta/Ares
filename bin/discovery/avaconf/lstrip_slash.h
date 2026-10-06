// https://github.com/Senzdetta/Ares

#ifndef lstrip_slash_h
#define lstrip_slash_h

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