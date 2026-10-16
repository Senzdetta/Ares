// https://github.com/Senzdetta/Ares

#ifndef handle_ctmod_h
#define handle_ctmod_h

#include <stdio.h>
#include <stdlib.h>

#include <lib/std/c/color.h>

#include <read_lines.h>
#include <find_group_end.h>
#include <insert_mod_line.h>

static inline int handle_ctmod(
    const char *filepath,
    const char *mod_name,
    const char *llsi_file,
    const char *group_name
) {
    int count = 0;
    char **lines = read_lines(
        filepath, &count
    );

    if (!lines) {
        return 1;
    }

    int ret = 1;
    int insert_idx = find_group_end(
        lines, count, group_name
    );

    if (
        insert_idx != -1 &&
        insert_mod_line(
            filepath, lines, count,
            insert_idx, mod_name, llsi_file
        ) == 0
    ) {
        printf(
            "%s[+] %sAdd new module (disabled): %s%s %s-> %s%s %sfor group %s%s%s\n",
            color_GG, color_N, color_GG, mod_name,
            color_DG, color_GG, llsi_file,
            color_N, color_GG, group_name, color_N
        );
        ret = 0;
    }

    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }

    free(lines);
    return ret;
}

#endif

// Copyright (c) 2026 Senzdetta