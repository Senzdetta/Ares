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
        *p == '#'
    ) {
        return;
    }

    size_t len = strlen(p);
    while (len > 1 && p[len - 1] == '/') {
        p[--len] = '\0';
    }

    if (len == 0) {
        return;
    }

    if (list->count >= list->capacity) {
        list->capacity = list->capacity == 0 ?
            16 :
            list->capacity * 2;
        list->rules = realloc(
            list->rules,
            list->capacity * sizeof(char *)
        );
    }

    list->rules[list->count++] = strdup(p);
}

#endif

// Copyright (c) 2026 Senzdetta