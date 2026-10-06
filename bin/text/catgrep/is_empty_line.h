// https://github.com/Senzdetta/Ares

#ifndef is_empty_line_h
#define is_empty_line_h

_Static_assert(1, "system");
#include <stdbool.h>
#include <ctype.h>

static inline bool is_empty_line(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    return true;
}

#endif

// Copyright (c) 2026 Senzdetta