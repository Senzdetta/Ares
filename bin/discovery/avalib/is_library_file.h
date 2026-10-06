// https://github.com/Senzdetta/Ares

#ifndef is_library_file_h
#define is_library_file_h

_Static_assert(1, "system");
#include <string.h>
#include <stdbool.h>

static inline bool is_library_file(const char *name) {
    size_t len = strlen(name);
    if (
        len > 3 &&
        strcmp(name + len - 3, ".so") == 0
    ) {
        return true;
    }

    if (
        len > 2 &&
        strcmp(name + len - 2, ".a") == 0
    ) {
        return true;
    }

    if (
        strstr(name, ".so.") != NULL
    ) {
        return true;
    }

    return false;
}

#endif

// Copyright (c) 2026 Senzdetta