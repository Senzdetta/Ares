// https://github.com/Senzdetta/Ares

#ifndef handle_ctgroup_h
#define handle_ctgroup_h

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <lib/std/c/color.h>

#include <group.h>
#include <parse_init_file.h>
#include <free_groups.h>

static inline int handle_ctgroup(
    const char *filepath,
    const char *group_name
) {
    Group *groups = NULL;
    int group_count = 0;
    parse_init_file(
        filepath,
        &groups,
        &group_count
    );

    for (int i = 0; i < group_count; i++) {
        if (strcmp(groups[i].name, group_name) == 0) {
            fprintf(
                stderr,
                "%s[!] %sGroup: %s%s %sis already exist!\n",
                color_R, color_N, color_GG, group_name, color_N
            );
            free_groups(groups, group_count);
            return 1;
        }
    }

    if (groups) {
        free_groups(groups, group_count);
    }

    FILE *out = fopen(filepath, "a");
    if (!out) {
        out = fopen(filepath, "w");
        if (!out) {
            fprintf(
                stderr,
                "%s[!] %sFailed to open/create file: %s%s %s(%s%s%s)%s\n",
                color_R, color_N, color_GG, filepath,
                color_DG, color_GG, strerror(errno), color_DG, color_N
            );
            return 1;
        }
    }

    fprintf(
        out,
        "\n//%s {\n//}\n",
        group_name
    );

    fclose(out);

    printf(
        "%s[+] %sCreate new group (disabled): %s%s%s\n",
        color_GG, color_N, color_GG, group_name, color_N
    );

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta