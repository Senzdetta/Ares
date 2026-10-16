// https://github.com/Senzdetta/Ares

#ifndef parse_init_file_h
#define parse_init_file_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <lib/std/c/color.h>

#include <group.h>
#include <module.h>
#include <trim_whitespace.h>
#include <add_group.h>
#include <add_module.h>

static inline int parse_init_file(
    const char *filepath,
    Group **groups_out,
    int *group_count_out
) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(
            stderr,
            "%s[!] %sFailed to open: %s%s%s\n",
            color_R, color_N, color_GG, filepath, color_N
        );

        *groups_out = NULL;
        *group_count_out = 0;

        return 1;
    }

    int group_cap = 10;
    int group_count = 0;
    Group *groups = malloc(
        group_cap * sizeof(Group)
    );

    if (!groups) {
        fclose(file);
        return 0;
    }

    char *line = NULL;
    size_t line_buf_size = 0;
    ssize_t line_len;
    Group *current = NULL;

    while (
        (
            line_len = getline(
                &line, &line_buf_size,
                file
            )
        ) != -1
    ) {
        if (
            line_len > 0 &&
            (
                line[line_len - 1] == '\n' ||
                line[line_len - 1] == '\r'
            )
        ) {
            line[line_len - 1] = '\0';
        }

        char *trimmed = trim_whitespace(line);
        if (trimmed[0] == '\0') {
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

        if (
            strstr(trimmed, "{") &&
            !strstr(trimmed, "->")
        ) {
            char *tmp = strdup(body);
            char *brace = strstr(tmp, "{");
            if (brace) {
                *brace = '\0';
            }

            char *name = strdup(trim_whitespace(tmp));
            free(tmp);

            current = add_group(
                &groups, &group_count, &group_cap,
                name, is_disabled
            );

            if (!current) {
                break;
            }

            continue;
        }

        if (
            strcmp(trimmed, "}") == 0 ||
            strcmp(trimmed, "//}") == 0
        ) {
            current = NULL;
            continue;
        }

        if (current && strstr(trimmed, "->")) {
            char mname[128] = "";
            sscanf(
                body, "%127s", mname
            );

            if (
                add_module(
                    current, strdup(body),
                    mname, is_disabled
                )
            ) {
                break;
            }
        }
    }

    free(line);
    fclose(file);

    *groups_out = groups;
    *group_count_out = group_count;

    return 1;
}

#endif

// Copyright (c) 2026 Senzdetta