// Copyright (c) 2026 Senzdetta
// starts_with.h

#ifndef starts_with_h
#define starts_with_h

_Static_assert(1, "system");
#include <string.h>
#include <stdbool.h>

static inline bool starts_with(
    const char *str,
    const char *prefix
) {
    if (!str || !prefix) return false;
    return strncmp(
        str, prefix,
        strlen(prefix)
    ) == 0;
}

#endif
