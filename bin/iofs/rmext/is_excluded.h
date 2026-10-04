// https://github.com/Senzdetta/Ares

#ifndef IS_EXCLUDED_H
#define IS_EXCLUDED_H

#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <add_exclude_rule.h>
#include <exclude_list.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

static inline int is_excluded(
    const char *path,
    ExcludeList *list
) {
    if (!list || !list->rules || !path) {
        return 0;
    }

    char clean_path[PATH_MAX];
    strncpy(
        clean_path,
        path,
        sizeof(clean_path) - 1
    );

    clean_path[sizeof(clean_path) - 1] = '\0';
    size_t plen = strlen(clean_path);

    while (plen > 1 && clean_path[plen - 1] == '/') {
        clean_path[--plen] = '\0';
    }

    for (size_t i = 0; i < list->count; i++) {
        size_t rlen = strlen(list->rules[i]);
        if (plen >= rlen) {
            if (
                strcmp(
                    clean_path + plen - rlen,
                    list->rules[i]
                ) == 0
            ) {
                if (
                    plen == rlen ||
                    clean_path[plen - rlen - 1] == '/'
                ) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta