// https://github.com/Senzdetta/Ares

#ifndef is_number_h
#define is_number_h

#include <stdbool.h>
#include <ctype.h>

static inline bool is_number(const char *str) {
    if (*str == '\0') {
        return false;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return false;
        }
    }

    return true;
}

#endif

// Copyright (c) 2026 Senzdetta