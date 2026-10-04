// https://github.com/Zeronetsec/Ares

#ifndef FREE_IGNORED_LIST_H
#define FREE_IGNORED_LIST_H

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <ignored_list.h>

static inline void free_ignored_list(IgnoredList *list) {
    if (!list) {
        return;
    }

    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i]);
    }

    free(list->items);

    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

#endif

// Copyright (c) 2026 Zeronetsec