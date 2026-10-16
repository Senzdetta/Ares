// https://github.com/Senzdetta/Ares

#ifndef rename_group_line_h
#define rename_group_line_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/std/c/color.h>
#include <trim_whitespace.h>

static inline int rename_group_line(
    char **lines,
    int count,
    const char *old_group,
    const char *new_group
) {
    char header[256];
    char header_off[256];

    snprintf(
        header, sizeof(header),
        "%s {",
        old_group
    );

    snprintf(
        header_off, sizeof(header_off),
        "//%s {",
        old_group
    );

    for (int i = 0; i < count; i++) {
        char *trimmed = trim_whitespace(lines[i]);

        if (
            strncmp(
                trimmed, header,
                strlen(header)
            ) != 0 &&
            strncmp(
                trimmed, header_off,
                strlen(header_off)
            ) != 0
        ) {
            continue;
        }

        int is_disabled = strncmp(
            trimmed, "//", 2
        ) == 0;

        char indent[64];
        int n = 0;

        while (
            (
                lines[i][n] == ' ' ||
                lines[i][n] == '\t'
            ) &&
            n < 63
        ) {
            indent[n] = lines[i][n];
            n++;
        }

        indent[n] = '\0';

        char new_line[512];
        snprintf(
            new_line, sizeof(new_line),
            "%s%s%s {",
            indent,
            is_disabled ?
                "//" :
                "",
            new_group
        );

        free(lines[i]);
        lines[i] = strdup(new_line);
        return 0;
    }

    fprintf(
        stderr,
        "%s[!] %sGroup: %s%s %snot found!\n",
        color_R, color_N, color_GG, old_group, color_N
    );

    return 1;
}

#endif

// Copyright (c) 2026 Senzdetta