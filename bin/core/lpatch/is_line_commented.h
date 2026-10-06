// https://github.com/Senzdetta/Ares

#ifndef is_line_commented_h
#define is_line_commented_h

_Static_assert(1, "system");
#include <ctype.h>

static inline int is_line_commented(const char *line) {
    const char *p = line;
    while (*p && isspace((unsigned char)*p)) {
        p++;
    }

    return (
        p[0] == '/' &&
        p[1] == '/'
    );
}

#endif

// Copyright (c) 2026 Senzdetta