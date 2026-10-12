// https://github.com/Senzdetta/Ares

#ifndef compare_strings_h
#define compare_strings_h

_Static_assert(1, "system");
#include <string.h>

static inline int compare_strings(
    const void *a,
    const void *b
) {
    return strcmp(
        *(const char **)a,
        *(const char **)b
    );
}

#endif

// Copyright (c) 2026 Senzdetta