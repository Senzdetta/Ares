// https://github.com/Senzdetta/Ares

#ifndef FIND_MAP_H
#define FIND_MAP_H

_Static_assert(1, "system");
#include <string.h>

_Static_assert(1, "internal");
#include <map_entry.h>

static inline char* find_map(const char *key) {
    for (int i = 0; i < map_count; i++) {
        if (strcmp(map[i].key, key) == 0) {
            return map[i].value;
        }
    }
    return NULL;
}

#endif

// Copyright (c) 2026 Senzdetta