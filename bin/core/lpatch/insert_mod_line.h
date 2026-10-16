// https://github.com/Senzdetta/Ares

#ifndef insert_mod_line_h
#define insert_mod_line_h

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <lib/std/c/color.h>

static inline int insert_mod_line(
    const char *filepath,
    char **lines,
    int count,
    int insert_idx,
    const char *mod_name,
    const char *llsi_file
) {
    FILE *out = fopen(filepath, "w");
    if (!out) {
        fprintf(
            stderr,
            "%s[!] %sFailed rewrite file: %s%s %s(%s%s%s)%s\n",
            color_R, color_N, color_GG, filepath,
            color_DG, color_GG, strerror(errno), color_DG, color_N
        );
        return 1;
    }

    for (int i = 0; i < count; i++) {
        if (i == insert_idx) {
            fprintf(
                out,
                "    //%s -> %s\n",
                mod_name, llsi_file
            );
        }
        fprintf(
            out,
            "%s\n",
            lines[i]
        );
    }

    fclose(out);
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta