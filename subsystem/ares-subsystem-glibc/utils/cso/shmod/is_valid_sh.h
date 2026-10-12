// https://github.com/Senzdetta/Ares

#ifndef is_valid_sh_h
#define is_valid_sh_h

_Static_assert(1, "system");
#include <stdio.h>
#include <ctype.h>

static inline int is_valid_sh(const char *filepath) {
    FILE *f = fopen(filepath, "r");
    if (!f) return 0;

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        char *p = line;

        while (*p && isspace((unsigned char)*p)) {
            p++;
        }

        if (
            *p != '\0' &&
            *p != '\n' &&
            *p != '#'
        ) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta