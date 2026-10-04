// https://github.com/Senzdetta/Ares

#ifndef STRIP_SLASHES_H
#define STRIP_SLASHES_H

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