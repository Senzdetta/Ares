// https://github.com/Senzdetta/Ares

#ifndef parse_scandup_h
#define parse_scandup_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <trim_whitespace.h>
#include <scan_data.h>
#include <add_scan_group.h>
#include <add_scan_mod.h>

static inline void parse_scandup(FILE *file, ScanData *d) {
    char *line = NULL;
    size_t line_buf_size = 0;
    ssize_t line_len;

    char current_group[128] = "";
    int in_active_group = 0;
    int line_no = 0;

    while (
        (
            line_len = getline(
                &line, &line_buf_size,
                file
            )
        ) != -1
    ) {
        line_no++;
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
        if (strlen(trimmed) == 0) {
            continue;
        }

        int is_disabled = strncmp(
            trimmed, "//", 2
        ) == 0;

        if (
            strstr(trimmed, "{") &&
            strstr(trimmed, "->") == NULL
        ) {
            if (is_disabled) {
                in_active_group = 0;
                current_group[0] = '\0';
                continue;
            }

            char gname[128];
            snprintf(
                gname, sizeof(gname),
                "%s",
                trimmed
            );

            char *b = strstr(gname, "{");
            if (b) {
                *b = '\0';
            }

            char *clean = trim_whitespace(gname);
            add_scan_group(
                d, clean, line_no
            );

            snprintf(
                current_group, sizeof(current_group),
                "%s",
                clean
            );

            in_active_group = 1;
            continue;
        }

        if (
            strcmp(trimmed, "}") == 0 ||
            strcmp(trimmed, "//}") == 0
        ) {
            in_active_group = 0;
            current_group[0] = '\0';
            continue;
        }

        if (
            in_active_group &&
            !is_disabled &&
            current_group[0] &&
            strstr(trimmed, "->")
        ) {
            char mname[128];
            char arrow[16];
            char dest[256];

            if (
                sscanf(
                    trimmed,
                    "%127s %15s %255s",
                    mname, arrow, dest
                ) >= 3
            ) {
                add_scan_mod(
                    d, mname, dest,
                    current_group, line_no
                );
            }
        }
    }

    free(line);
}

#endif

// Copyright (c) 2026 Senzdetta