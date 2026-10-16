// https://github.com/Senzdetta/Ares

#ifndef handle_rnmod_h
#define handle_rnmod_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <lib/std/c/color.h>

#include <read_lines.h>
#include <rename_mod_line.h>

static inline int handle_rnmod(
    const char *filepath,
    const char *old_mod,
    const char *new_mod,
    const char *new_dest
) {
    int count = 0;
    char **lines = read_lines(
        filepath, &count
    );

    if (!lines) {
        return 1;
    }

    int ret = rename_mod_line(
        lines, count, old_mod,
        new_mod, new_dest
    );

    if (ret == 0) {
        FILE *out = fopen(filepath, "w");
        if (!out) {
            fprintf(
                stderr,
                "%s[!] %sFailed to rewrite file: %s%s %s(%s%s%s)%s\n",
                color_R, color_N, color_GG, filepath,
                color_DG, color_GG, strerror(errno), color_DG, color_N
            );
            ret = 1;
        } else {
            for (int i = 0; i < count; i++) {
                fprintf(
                    out,
                    "%s\n",
                    lines[i]
                );
            }

            fclose(out);

            printf(
                "%s[+] %sRenamed mod: %s%s %s-> %s%s%s\n",
                color_GG, color_N, color_GG, old_mod,
                color_DG, color_GG, new_mod, color_N
            );
        }
    }

    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }

    free(lines);
    return ret;
}

#endif

// Copyright (c) 2026 Senzdetta