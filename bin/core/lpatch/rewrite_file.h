// https://github.com/Senzdetta/Ares

#ifndef rewrite_file_h
#define rewrite_file_h

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <lib/std/c/color.h>

#include <trim_whitespace.h>
#include <write_toggled.h>

static inline int rewrite_file(
    const char *filepath,
    char **lines,
    int count,
    const char *group,
    const char *mod,
    int enable
) {
    FILE *out = fopen(filepath, "w");
    if (!out) {
        fprintf(
            stderr,
            "%s[!] %sFailed to open file: %s%s %s(%s%s%s)%s\n",
            color_R, color_N, color_GG, filepath,
            color_DG, color_GG, strerror(errno), color_DG, color_N
        );
        return 1;
    }

    char header[256];
    char header_off[256];

    snprintf(
        header, sizeof(header),
        "%s {",
        group
    );

    snprintf(
        header_off, sizeof(header_off),
        "//%s {",
        group
    );

    int in_group = 0;

    for (int i = 0; i < count; i++) {
        char *raw = lines[i];
        char *trimmed = trim_whitespace(raw);
        int disabled = strncmp(
            trimmed, "//", 2
        ) == 0;

        int is_header = (
            strncmp(
                trimmed, header,
                strlen(header)
            ) == 0 ||
            strncmp(
                trimmed, header_off,
                strlen(header_off)
            ) == 0
        );

        int is_end = in_group && (
            strcmp(trimmed, "}") == 0 ||
            strcmp(trimmed, "//}") == 0
        );

        if (is_header || is_end) {
            in_group = is_header;
            if (!mod && enable == disabled) {
                write_toggled(
                    out, raw, enable
                );
                continue;
            }
        } else if (in_group) {
            char *body = trim_whitespace(
                disabled ?
                    trimmed + 2 :
                    trimmed
            );

            char mod_name[128];

            if (
                sscanf(
                    body,
                    "%127s ->",
                    mod_name
                ) == 1 &&
                (
                    !mod ||
                    strcmp(mod_name, mod) == 0
                ) &&
                enable == disabled
            ) {
                write_toggled(
                    out, raw, enable
                );
                continue;
            }
        }
        fprintf(
            out,
            "%s\n",
            raw
        );
    }

    fclose(out);
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta