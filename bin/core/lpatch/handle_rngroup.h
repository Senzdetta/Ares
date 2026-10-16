// https://github.com/Senzdetta/Ares

#ifndef handle_rngroup_h
#define handle_rngroup_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <lib/std/c/color.h>

#include <read_lines.h>
#include <rename_group_line.h>

static inline int handle_rngroup(
    const char *filepath,
    const char *old_group,
    const char *new_group
) {
    int count = 0;
    char **lines = read_lines(
        filepath, &count
    );

    if (!lines) {
        return 1;
    }

    int ret = rename_group_line(
        lines, count,
        old_group, new_group
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
                "%s[+] %sRenamed group name: %s%s %s-> %s%s%s\n",
                color_GG, color_N, color_GG, old_group,
                color_DG, color_GG, new_group, color_N
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