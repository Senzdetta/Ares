// https://github.com/Senzdetta/Ares

#ifndef trim_line_h
#define trim_line_h

_Static_assert(1, "system");
#include <ctype.h>
#include <string.h>

static inline char *trim_line(char *line) {
    while (isspace((unsigned char)*line)) line++;

    char *end = line + strlen(line) - 1;
    while (
        end >= line &&
        isspace((unsigned char)*end)
    ) {
        *end = '\0';
        end--;
    }

    return line;
}

#endif

// Copyright (c) 2026 Senzdetta