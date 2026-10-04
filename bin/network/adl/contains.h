// https://github.com/Zeronetsec/Ares

#ifndef CONTAINS_H
#define CONTAINS_H

_Static_assert(1, "system");
#include <stdbool.h>
#include <string.h>

static inline bool contains(
    const char *str,
    const char *sub
) {
    return strstr(str, sub) != NULL;
}

#endif

// Copyright (c) 2026 Zeronetsec