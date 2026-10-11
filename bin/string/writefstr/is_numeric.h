// https://github.com/Senzdetta/Ares

#ifndef is_numeric_h
#define is_numeric_h

#include <ctype.h>

static inline int is_numeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

#endif

// Copyright (c) 2026 Senzdetta