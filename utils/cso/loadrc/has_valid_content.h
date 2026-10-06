// https://github.com/Senzdetta/Ares

#ifndef has_valid_content_h
#define has_valid_content_h

_Static_assert(1, "system");
#include <stdio.h>
#include <ctype.h>

static inline int has_valid_content(const char *filename) {
    if (!filename || !*filename) return 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    char line[1024];
    int valid = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *ptr = line;
        while (isspace((unsigned char)*ptr)) ptr++;

        if (
            *ptr != '\0' &&
            *ptr != '#' &&
            *ptr != '\n' &&
            *ptr != '\r'
        ) {
            valid = 1;
            break;
        }
    }

    fclose(fp);
    return valid;
}

#endif

// Copyright (c) 2026 Senzdetta