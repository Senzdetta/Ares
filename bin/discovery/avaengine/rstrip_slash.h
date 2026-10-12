// Copyright (c) 2026 Senzdetta
// rstrip_slash.h

#ifndef rstrip_slash_h
#define rstrip_slash_h

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
