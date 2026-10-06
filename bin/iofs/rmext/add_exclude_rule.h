// https://github.com/Senzdetta/Ares

#ifndef add_exclude_rule_h
#define add_exclude_rule_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <trim_whitespace.h>
#include <exclude_list.h>

static inline void add_exclude_rule(
    ExcludeList *list,
    const char *rule_str
) {
    char *p = trim_whitespace((char *)rule_str);
    if (
        *p == '\0' ||
        (
            p[0] == '/' &&
            p[1] == '/'
        )
    ) {
        return;
    }

    char *first_quote = strchr(p, '"');
    if (!first_quote) return;

    char *second_quote = strchr(first_quote + 1, '"');
    if (!second_quote) return;

    char *from_word = strstr(second_quote + 1, "from");
    if (!from_word) return;

    char *third_quote = strchr(from_word, '"');
    if (!third_quote) return;

    char *fourth_quote = strchr(third_quote + 1, '"');
    if (!fourth_quote) return;

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
                list->capacity * sizeof(char *)
            );
        }
        list->rules[list->count++] = strdup(combined);
    }
}

#endif

// Copyright (c) 2026 Senzdetta