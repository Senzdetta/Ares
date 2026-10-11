// https://github.com/Senzdetta/Ares

#ifndef printp_h
#define printp_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <color.h>

static inline int printp(void) {
    char *path = getenv("PATH");
    if (path == NULL) {
        printf(
            "%s[!] %sVariable: %s$PATH %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        return 1;
    }

    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        fprintf(
            stderr,
            "%s[!] %sFailed to allocate memory: %s%s%s\n",
            color_R, color_N, color_GG, strerror(errno), color_N
        );
        return 1;
    }

    char *dir = strtok(path_copy, ":");
    while (dir != NULL) {
        printf(
            "%s› %s%s%s\n",
            color_R, color_GG, dir, color_N
        );
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta