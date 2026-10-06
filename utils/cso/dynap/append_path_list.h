// https://github.com/Senzdetta/Ares

#ifndef append_path_list_h
#define append_path_list_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <exclude_list.h>
#include <string_buffer.h>
#include <append_path.h>

static inline void append_path_list(
    StringBuffer *sb,
    const char *path_list
) {
    if (!path_list || !*path_list) {
        return;
    }

    char *dup = strdup(path_list);
    if (!dup) return;

    char *token = strtok(dup, ":");
    while (token) {
        append_path(sb, token);
        token = strtok(NULL, ":");
    }

    free(dup);
}

#endif

// Copyright (c) 2026 Senzdetta