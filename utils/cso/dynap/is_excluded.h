// https://github.com/Senzdetta/Ares

#ifndef is_excluded_h
#define is_excluded_h

_Static_assert(1, "system");
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <exclude_list.h>

static inline int is_excluded(
    const char *path,
    ExcludeList *list
) {
    if (!list || !list->rules || !path) {
        return 0;
    }

    char clean_path[PATH_MAX];
    strncpy(
        clean_path, path,
        sizeof(clean_path) - 1
    );
    clean_path[sizeof(clean_path) - 1] = '\0';

    size_t plen = strlen(clean_path);
    while (plen > 1 && clean_path[plen - 1] == '/') {
        clean_path[--plen] = '\0';
    }

    for (size_t i = 0; i < list->count; i++) {
        size_t rlen = strlen(list->rules[i]);
        if (strncmp(clean_path, list->rules[i], rlen) == 0) {
            if (
                clean_path[rlen] == '\0' ||
                clean_path[rlen] == '/'
            ) {
                return 1;
            }
        }
    }

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta