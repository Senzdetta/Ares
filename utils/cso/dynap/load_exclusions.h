// https://github.com/Zeronetsec/Ares

#ifndef LOAD_EXCLUSIONS_H
#define LOAD_EXCLUSIONS_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <trim_whitespace.h>
#include <exclude_list.h>

static inline void load_exclusions(
    const char *config_dir,
    ExcludeList *list
) {
    if (!config_dir || !*config_dir) {
        return;
    }

    char filepath[PATH_MAX];
    snprintf(
        filepath,
        sizeof(filepath),
        "%s/dynap_exclude.scfg",
        config_dir
    );

    FILE *fp = fopen(filepath, "r");
    if (!fp) return;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *p = trim_whitespace(line);
        if (
            *p == '\0' ||
            (p[0] == '/' && p[1] == '/')
        ) {
            continue;
        }

        char *first_quote = strchr(p, '"');
        if (!first_quote) {
            continue;
        }

        char *second_quote = strchr(first_quote + 1, '"');
        if (!second_quote) {
            continue;
        }

        char *from_word = strstr(second_quote + 1, "from");
        if (!from_word) {
            continue;
        }

        char *third_quote = strchr(from_word, '"');
        if (!third_quote) {
            continue;
        }

        char *fourth_quote = strchr(third_quote + 1, '"');
        if (!fourth_quote) {
            continue;
        }

        size_t t_len = second_quote - (first_quote + 1);
        size_t p_len = fourth_quote - (third_quote + 1);

        if (
            t_len > 0 &&
            p_len > 0 &&
            t_len < 256 &&
            p_len < 256
        ) {
            char target[256] = {0};
            char parent[256] = {0};

            strncpy(
                target,
                first_quote + 1,
                t_len
            );

            strncpy(
                parent,
                third_quote + 1,
                p_len
            );

            char combined[1024];
            snprintf(
                combined,
                sizeof(combined),
                "%s/%s",
                parent, target
            );

            if (list->count >= list->capacity) {
                list->capacity = list->capacity == 0 ?
                    16 :
                    list->capacity * 2;
                list->rules = realloc(
                    list->rules,
                    list->capacity * sizeof(char*)
                );
            }
            list->rules[list->count++] = strdup(combined);
        }
    }
    fclose(fp);
}

#endif

// Copyright (c) 2026 Zeronetsec