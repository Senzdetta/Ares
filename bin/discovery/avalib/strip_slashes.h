// https://github.com/Senzdetta/Ares

#ifndef strip_slashes_h
#define strip_slashes_h

_Static_assert(1, "internal");
#include <rstrip_slash.h>

static inline char *strip_slashes(char *str) {
    if (!str) return NULL;
    while (*str == '/') str++;
    rstrip_slash(str);
    return str;
}

#endif

// Copyright (c) 2026 Senzdetta