// https://github.com/Senzdetta/Ares

#ifndef scan_llsi_state_h
#define scan_llsi_state_h

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>

_Static_assert(1, "internal");
#include <mode.h>
#include <trim.h>
#include <starts_with.h>
#include <is_line_commented.h>

static inline int scan_llsi_state(
    FILE *f,
    Mode mode,
    const char *group,
    const char *group_header,
    const char *mod_name,
    int *group_found,
    int *mod_found,
    int *state_already_matched,
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
            *group_found = 1;
            in_target_group = 1;
            continue;
        }

        if (in_target_group) {
            if (trimmed[0] == '}') {
                in_target_group = 0;
                continue;
            }

            if (mod_name) {
                char search_pattern[256];
                snprintf(
                    search_pattern, sizeof(search_pattern),
                    "%s ->", mod_name
                );

                if (strstr(trimmed, search_pattern) != NULL) {
                    *mod_found = 1;
                    int commented = is_line_commented(trimmed);
                    if (
                        (mode == MODE_DISABLE && commented) ||
                        (mode == MODE_ENABLE && !commented)
                    ) {
                        *state_already_matched = 1;
                    }
                }
            } else {
                if (strlen(trimmed) > 0) {
                    int commented = is_line_commented(trimmed);
                    if (mode == MODE_DISABLE && !commented) {
                        *mod_found = 1;
                    }

                    if (mode == MODE_ENABLE && commented) {
                        *mod_found = 1;
                    }
                }
            }
        }
    }
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta