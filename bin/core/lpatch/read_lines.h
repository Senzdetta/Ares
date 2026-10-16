// https://github.com/Senzdetta/Ares

#ifndef read_lines_h
#define read_lines_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <lib/std/c/color.h>

static inline char **read_lines(
    const char *filepath,
    int *count
) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(
            stderr,
            "%s[!] %sFailed to open: %s%s %s(%s%s%s)%s\n",
            color_R, color_N, color_GG, filepath,
            color_DG, color_GG, strerror(errno), color_DG, color_N
        );
        return NULL;
    }

    int cap = 10;
    char **lines = malloc(
        cap * sizeof(char *)
    );

    char *buf = NULL;
    size_t buf_len = 0;

    ssize_t n;
    *count = 0;

    while (
        (
            n = getline(
                &buf, &buf_len,
                file
            )
        ) != -1
    ) {
        if (
            n > 0 &&
            (
                buf[n - 1] == '\n' ||
                buf[n - 1] == '\r'
            )
        ) {
            buf[n - 1] = '\0';
        }

        if (*count >= cap) {
            cap *= 2;
            lines = realloc(
                lines,
                cap * sizeof(char *)
            );
        }

        lines[(*count)++] = strdup(buf);
    }

    free(buf);
    fclose(file);

    return lines;
}

#endif

// Copyright (c) 2026 Senzdetta