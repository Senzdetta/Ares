// https://github.com/Senzdetta/Ares

#ifndef cmp_str_h
#define cmp_str_h

_Static_assert(1, "system");
#include <string.h>

static inline int cmp_str(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

#endif

// Copyright (c) 2026 Senzdetta