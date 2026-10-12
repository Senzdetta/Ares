// https://github.com/Senzdetta/Ares

#ifndef is_ignored_folder_h
#define is_ignored_folder_h

_Static_assert(1, "system");
#include <string.h>

_Static_assert(1, "system");
#include <ignored_list.h>

static inline int is_ignored_folder(
    const char *folder_name,
    const IgnoredList *list
) {
    if (!list || !list->items || !folder_name) {
        return 0;
    }

    for (size_t i = 0; i < list->count; i++) {
        if (strcmp(folder_name, list->items[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta