// https://github.com/Zeronetsec/Ares

#ifndef IS_PATH_REGISTERED_H
#define IS_PATH_REGISTERED_H

_Static_assert(1, "system");
#include <stdbool.h>
#include <string.h>

_Static_assert(1, "internal");
#include <registered_llsi_t.h>

static inline bool is_path_registered(
    const registered_llsi_t *reg,
    const char *rel_path
) {
    if (!reg || !rel_path) return false;
    for (size_t i = 0; i < reg->count; i++) {
        if (strcmp(reg->paths[i], rel_path) == 0) {
            return true;
        }
    }
    return false;
}

#endif

// Copyright (c) 2026 Zeronetsec