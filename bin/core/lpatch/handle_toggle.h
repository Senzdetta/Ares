// https://github.com/Senzdetta/Ares

#ifndef handle_toggle_h
#define handle_toggle_h

#include <stdio.h>
#include <stdlib.h>

#include <lib/std/c/color.h>

#include <scan_result.h>
#include <read_lines.h>
#include <scan_lines.h>
#include <rewrite_file.h>

static inline int handle_toggle(
    const char *filepath,
    int enable,
    const char *group,
    const char *mod
) {
    int count = 0;
    char **lines = read_lines(
        filepath, &count
    );

    if (!lines) {
        return 1;
    }

    ScanResult r;
    scan_lines(
        lines, count, group,
        mod, enable, &r
    );

    int ret = 0;
    if (!r.group_found) {
        fprintf(
            stderr,
            "%s[!] %sGroup: %s%s %snot found on %s%s%s\n",
            color_R, color_N, color_GG, group, color_N,
            color_GG, filepath, color_N
        );
        ret = 1;
    } else if (mod && r.mod_found_count == 0) {
        fprintf(
            stderr,
            "%s[!] %sMod: %s%s %snot found on group %s%s%s\n",
            color_R, color_N, color_GG, mod, color_N,
            color_GG, group, color_N
        );
        ret = 1;
    } else if (r.action_possible) {
        ret = rewrite_file(
            filepath, lines, count,
            group, mod, enable
        );
    }

    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }

    free(lines);
    return ret;
}

#endif

// Copyright (c) 2026 Senzdetta