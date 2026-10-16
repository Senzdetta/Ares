// https://github.com/Senzdetta/Ares

#ifndef rename_mod_line_h
#define rename_mod_line_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/std/c/color.h>
#include <trim_whitespace.h>

static inline int rename_mod_line(
    char **lines,
    int count,
    const char *old_mod,
    const char *new_mod,
    const char *new_dest
) {
    for (int i = 0; i < count; i++) {
        char *trimmed = trim_whitespace(lines[i]);

        if (
            trimmed[0] == '\0' ||
            !strstr(trimmed, "->")
        ) {
            continue;
        }

        int is_disabled = strncmp(
            trimmed, "//", 2
        ) == 0;

        char *body = trim_whitespace(
            is_disabled ?
                trimmed + 2 :
                trimmed
        );

        char mname[128];
        char arrow[16];
        char path[256] = "";

        if (
            sscanf(
                body,
                "%127s %15s %255s",
                mname, arrow, path
            ) < 2
        ) {
            continue;
        }

        if (strcmp(mname, old_mod) != 0) {
            continue;
        }

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
            "%s%s%s -> %s",
            indent,
            is_disabled ?
                "//" :
                "",
            new_mod,
            new_dest ?
                new_dest :
                path
        );

        free(lines[i]);
        lines[i] = strdup(new_line);

        return 0;
    }

    fprintf(
        stderr,
        "%s[!] %sMod: %s%s %snot found!\n",
        color_R, color_N, color_GG, old_mod, color_N
    );

    return 1;
}

#endif

// Copyright (c) 2026 Senzdetta