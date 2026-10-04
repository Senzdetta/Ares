// https://github.com/Senzdetta/Ares

#ifndef PRINT_FILE_CONTENT_H
#define PRINT_FILE_CONTENT_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>

_Static_assert(1, "ares");
#include <color.h>

static inline void print_file_content(const char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (!fp) {
        printf(
            "    %s[%sCannot read file%s]%s\n",
            color_DG, color_WW, color_DG, color_N
        );
        return;
    }

    char line[4096];
    while (fgets(line, sizeof(line), fp)) {
        printf(
            "%s    %s%s",
            color_WW, line, color_N
        );
    }

    size_t len = strlen(line);
    if (len > 0 && line[len - 1] != '\n') {
        printf("\n");
    }

    fclose(fp);
}

#endif

// Copyright (c) 2026 Senzdetta