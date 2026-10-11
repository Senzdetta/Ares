// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_trim_h
#define utils_crawlpath_trim_h

#include <string.h>

static inline void trim(char *s) {
    char *p = s;

    int l = strlen(p);
    while (
        l > 0 &&
        (
            p[l - 1] == ' ' ||
            p[l - 1] == '\t' ||
            p[l - 1] == '\n' ||
            p[l - 1] == '\r'
        )
    ) {
        p[--l] = '\0';
    }

    while (*p && (*p == ' ' || *p == '\t')) {
        p++;
    }

    if (p != s) {
        memmove(s, p, strlen(p) + 1);
    }
}

#endif

// Copyright (c) 2026 Senzdetta