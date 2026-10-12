// https://github.com/Senzdetta/Ares

#ifndef load_exclusions_h
#define load_exclusions_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <trim_whitespace.h>
#include <exclude_list.h>
#include <expand_vars.h>

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
        "%s/dynap_exclude.lst",
        config_dir
    );

    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *p = trim_whitespace(line);
        if (
            *p == '\0' ||
            *p == '#'
        ) {
            continue;
        }

        char expanded[PATH_MAX];
        expand_vars(
            p, expanded,
            sizeof(expanded)
        );

        char *clean_exp = trim_whitespace(expanded);
        if (*clean_exp == '\0') {
            continue;
        }

        if (list->count >= list->capacity) {
            list->capacity = list->capacity == 0 ?
                16 :
                list->capacity * 2;

            list->rules = realloc(
                list->rules,
                list->capacity * sizeof(char*)
            );
        }
        list->rules[list->count++] = strdup(clean_exp);
    }
    fclose(fp);
}

#endif

// Copyright (c) 2026 Senzdetta