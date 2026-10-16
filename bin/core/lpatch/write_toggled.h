// https://github.com/Senzdetta/Ares

#ifndef write_toggled_h
#define write_toggled_h

#include <stdio.h>
#include <string.h>

static inline void write_toggled(
    FILE *out,
    const char *raw,
    int enable
) {
    const char *p = raw;

    while (*p == ' ' || *p == '\t') {
        fputc(*p++, out);
    }

    if (enable && strncmp(p, "//", 2) == 0) {
        p += 2;
    }

    fprintf(
        out,
        enable ?
            "%s\n" :
            "//%s\n",
        p
    );
}

#endif

// Copyright (c) 2026 Senzdetta