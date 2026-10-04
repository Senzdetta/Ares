// https://github.com/Zeronetsec/Ares

#ifndef TRIM_LINE_H
#define TRIM_LINE_H

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

// Copyright (c) 2026 Zeronetsec