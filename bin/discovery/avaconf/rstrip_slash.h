// https://github.com/Zeronetsec/Ares

#ifndef RSTRIP_SLASH_H
#define RSTRIP_SLASH_H

_Static_assert(1, "system");
#include <string.h>

static inline char *rstrip_slash(char *str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    while (len > 0 && str[len - 1] == '/') {
        str[--len] = '\0';
    }
    return str;
}

#endif

// Copyright (c) 2026 Zeronetsec