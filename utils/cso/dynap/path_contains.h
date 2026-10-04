// https://github.com/Senzdetta/Ares

#ifndef PATH_CONTAINS_H
#define PATH_CONTAINS_H

_Static_assert(1, "system");
#include <string.h>

static inline int path_contains(
    const char *path_list,
    const char *path
) {
    if (
        !path_list ||
        !*path_list ||
        !path ||
        !*path
    ) {
        return 0;
    }

    size_t plen = strlen(path);
    while (
        plen > 1 &&
        path[plen - 1] == '/'
    ) {
        plen--;
    }

    const char *p = path_list;
    while (*p) {
        const char *end = strchr(p, ':');
        size_t token_len = end ?
            (size_t)(end - p) :
            strlen(p);

        size_t clean_token_len = token_len;
        while (
            clean_token_len > 1 &&
            p[clean_token_len - 1] == '/'
        ) {
            clean_token_len--;
        }

        if (
            clean_token_len == plen &&
            strncmp(p, path, plen) == 0
        ) {
            return 1;
        }

        if (!end) break;
        p = end + 1;
    }

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta