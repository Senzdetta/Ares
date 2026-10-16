// https://github.com/Senzdetta/Ares

#ifndef find_group_end_h
#define find_group_end_h

#include <stdio.h>
#include <string.h>

#include <lib/std/c/color.h>
#include <trim_whitespace.h>

static inline int find_group_end(
    char **lines,
    int count,
    const char *group_name
) {
    char header[256];
    char header_off[256];

    snprintf(
        header, sizeof(header),
        "%s {",
        group_name
    );

    snprintf(
        header_off, sizeof(header_off),
        "//%s {",
        group_name
    );

    int group_found = 0;

    for (int i = 0; i < count; i++) {
        char *trimmed = trim_whitespace(lines[i]);

        if (
            strncmp(
                trimmed,
                header,
                strlen(header)
            ) == 0 ||
            strncmp(
                trimmed,
                header_off,
                strlen(header_off)
            ) == 0
        ) {
            group_found = 1;
            continue;
        }

        if (
            group_found &&
            (
                strcmp(trimmed, "}") == 0 ||
                strcmp(trimmed, "//}") == 0
            )
        ) {
            return i;
        }
    }

    if (!group_found) {
        fprintf(
            stderr,
            "%s[!] %sGroup: %s%s %snot found!\n",
            color_R, color_N, color_GG, group_name, color_N
        );
    } else {
        fprintf(
            stderr,
            "%s[!] %sSyntax Error: invalid group closing format!\n",
            color_R, color_N
        );
    }

    return -1;
}

#endif

// Copyright (c) 2026 Senzdetta