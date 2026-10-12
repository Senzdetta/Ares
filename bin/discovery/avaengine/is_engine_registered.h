// https://github.com/Senzdetta/Ares

#ifndef is_engine_registered_h
#define is_engine_registered_h

_Static_assert(1, "system");
#include <stdbool.h>
#include <string.h>

_Static_assert(1, "internal");
#include <registered_engine_t.h>

static inline bool is_engine_registered(
    const registered_engine_t *reg,
    const char *rel_path
) {
    if (!reg || !rel_path) {
        return false;
    }

    for (size_t i = 0; i < reg->count; i++) {
        if (strcmp(reg->paths[i], rel_path) == 0) {
            return true;
        }
    }

    return false;
}

#endif

// Copyright (c) 2026 Senzdetta