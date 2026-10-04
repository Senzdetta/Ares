// https://github.com/Senzdetta/Ares

#ifndef STARTS_WITH_H
#define STARTS_WITH_H

_Static_assert(1, "system");
#include <string.h>

static inline int starts_with(
    const char *str,
    const char *prefix
) {
    return strncmp(
        str, prefix,
        strlen(prefix)
    ) == 0;
}

#endif

// Copyright (c) 2026 Senzdetta