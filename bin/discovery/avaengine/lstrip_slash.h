// Copyright (c) 2026 Senzdetta
// lstrip_slash.h

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
