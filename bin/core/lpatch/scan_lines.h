// https://github.com/Senzdetta/Ares

#ifndef scan_lines_h
#define scan_lines_h

#include <stdio.h>
#include <string.h>

#include <lib/std/c/color.h>

#include <trim_whitespace.h>
#include <scan_result.h>

static inline void scan_lines(
    char **lines,
    int count,
    const char *group,
    const char *mod,
    int enable, ScanResult *r
) {
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
    *r = (ScanResult){0};

    for (int i = 0; i < count; i++) {
        char *trimmed = trim_whitespace(lines[i]);
        int disabled = strncmp(
            trimmed, "//", 2
        ) == 0;

        if (
            strncmp(
                trimmed, header,
                strlen(header)
            ) == 0 ||
            strncmp(
                trimmed, header_off,
                strlen(header_off)
            ) == 0
        ) {
            in_group = 1;
            r->group_found = 1;

            if (mod) {
                continue;
            }

            if (enable == disabled) {
                r->action_possible = 1;
                printf(
                    "%s[*] %s%s group: %s%s%s\n",
                    color_B, color_N, enable ? "Enable" : "Disable",
                    color_GG, group, color_N
                );
            } else {
                printf(
                    "%s[!] %sGroup: %s%s %sis already %s!\n",
                    color_R, color_N, color_GG, group, color_N,
                    enable ? "active" : "disabled"
                );
            }
            continue;
        }

        if (!in_group) {
            continue;
        }

        if (
            strcmp(trimmed, "}") == 0 ||
            strcmp(trimmed, "//}") == 0
        ) {
            in_group = 0;
            continue;
        }

        char *body = trim_whitespace(
            disabled ?
                trimmed + 2 :
                trimmed
        );

        char mod_name[128];

        if (sscanf(body, "%127s ->", mod_name) != 1) {
            continue;
        }

        if (mod && strcmp(mod_name, mod) != 0) {
            continue;
        }

        r->mod_found_count++;

        if (enable == disabled) {
            r->action_possible = 1;
            printf(
                "%s[*] %s%s mod: %s%s %sfrom group %s%s%s\n",
                color_B, color_N, enable ? "Enable" : "Disable",
                color_GG, mod_name, color_N, color_GG, group, color_N
            );
        } else {
            printf(
                "%s[!] %sMod: %s%s %sfrom group %s%s %sis already %s!\n",
                color_R, color_N, color_GG, mod_name, color_N,
                color_GG, group, color_N,
                enable ? "active" : "disabled"
            );
        }
    }
}

#endif

// Copyright (c) 2026 Senzdetta