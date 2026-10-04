// https://github.com/Zeronetsec/Ares

#ifndef PARSE_LLSI_INIT_H
#define PARSE_LLSI_INIT_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

_Static_assert(1, "internal");
#include <registered_llsi_t.h>
#include <strip_slashes.h>
#include <add_registered_path.h>

static inline bool parse_llsi_init(
    const char *init_file_path,
    registered_llsi_t *reg
) {
    FILE *fp = fopen(init_file_path, "r");
    if (!fp) return false;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *comment = strstr(line, "//");
        if (comment) {
            *comment = '\0';
        }

        char *arrow = strstr(line, "->");
        if (arrow) {
            char *target = arrow + 2;
            while (*target == ' ' || *target == '\t') {
                target++;
            }

            char *end = target;
            while (
                *end &&
                *end != '\n' &&
                *end != '\r' &&
                *end != ' ' &&
                *end != '\t'
            ) {
                end++;
            }
            *end = '\0';

            if (strlen(target) > 0) {
                char *clean_target = strdup(target);
                clean_target = strip_slashes(clean_target);
                add_registered_path(reg, clean_target);
                free(clean_target);
            }
        }
    }
    fclose(fp);
    return true;
}

#endif

// Copyright (c) 2026 Zeronetsec