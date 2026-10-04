// https://github.com/Zeronetsec/Ares

#ifndef PATCH_LLSI_FILE_H
#define PATCH_LLSI_FILE_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <ctype.h>

_Static_assert(1, "internal");
#include <mode.h>
#include <trim.h>
#include <starts_with.h>
#include <is_line_commented.h>

static inline void patch_llsi_file(
    FILE *f,
    FILE *tmp,
    Mode mode,
    const char *group,
    const char *group_header,
    const char *mod_name,
    const char *mod_val,
    size_t max_line
) {
    char line[max_line];
    int in_target_group = 0;

    while (fgets(line, max_line, f)) {
        char trimmed[max_line];
        strcpy(trimmed, line);
        trim(trimmed);

        if (
            starts_with(trimmed, group_header) ||
            strcmp(trimmed, group) == 0
        ) {
            in_target_group = 1;
            fputs(line, tmp);
            continue;
        }

        if (in_target_group) {
            if (trimmed[0] == '}') {
                in_target_group = 0;
                fputs(line, tmp);
                continue;
            }

            if (mode == MODE_DISABLE || mode == MODE_ENABLE) {
                int target_this_line = 0;

                if (mod_name) {
                    char search_pattern[256];
                    snprintf(
                        search_pattern, sizeof(search_pattern),
                        "%s ->", mod_name
                    );

                    if (strstr(trimmed, search_pattern) != NULL) {
                        target_this_line = 1;
                    }
                } else {
                    target_this_line = 1;
                }

                if (target_this_line) {
                    if (
                        mode == MODE_DISABLE &&
                        !is_line_commented(line)
                    ) {
                        char *p = line;
                        while (
                            *p &&
                            isspace((unsigned char)*p)
                        ) {
                            fputc(*p++, tmp);
                        }
                        fputs("// ", tmp);
                        fputs(p, tmp);
                        continue;
                    } else if (
                        mode == MODE_ENABLE &&
                        is_line_commented(line)
                    ) {
                        char *p = strstr(line, "//");
                        if (p) {
                            p += 2;
                            if (*p == ' ') p++;
                            char *leading = line;
                            while (
                                leading < strstr(line, "//")
                            ) {
                                fputc(*leading++, tmp);
                            }
                            fputs(p, tmp);
                            continue;
                        }
                    }
                }
            }
        }
        fputs(line, tmp);
    }

    if (mode == MODE_CREATE) {
        fprintf(tmp, "\n%s {\n", group);
        if (mod_name && mod_val) {
            fprintf(
                tmp, "    %s -> %s.llsi\n",
                mod_name, mod_val
            );
        }
        fprintf(tmp, "}\n");
    }
}

#endif

// Copyright (c) 2026 Zeronetsec