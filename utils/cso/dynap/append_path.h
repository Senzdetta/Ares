// https://github.com/Senzdetta/Ares

#ifndef APPEND_PATH_H
#define APPEND_PATH_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <string_buffer.h>
#include <path_contains.h>

static inline void append_path(
    StringBuffer *sb,
    const char *path
) {
    if (!path || !*path) {
        return;
    }

    char clean_path[PATH_MAX];
    strncpy(
        clean_path,
        path,
        sizeof(clean_path) - 1
    );
    clean_path[sizeof(clean_path) - 1] = '\0';

    size_t plen = strlen(clean_path);
    while (
        plen > 1 &&
        clean_path[plen - 1] == '/'
    ) {
        clean_path[--plen] = '\0';
    }

    if (
        sb->str &&
        path_contains(
            sb->str, clean_path
        )
    ) {
        return;
    }

    if (sb->len + plen + 2 > sb->capacity) {
        sb->capacity = (sb->capacity + plen + 1024) * 2;
        char *new_str = realloc(
            sb->str,
            sb->capacity
        );
        if (!new_str) return;
        sb->str = new_str;
    }

    if (sb->len > 0) {
        sb->str[sb->len++] = ':';
    }

    strcpy(
        sb->str + sb->len,
        clean_path
    );

    sb->len += plen;
}

#endif

// Copyright (c) 2026 Senzdetta