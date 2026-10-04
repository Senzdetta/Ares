// https://github.com/Zeronetsec/Ares

#ifndef FREE_REGISTERED_LLSI_H
#define FREE_REGISTERED_LLSI_H

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <registered_llsi_t.h>

static inline void free_registered_llsi(
    registered_llsi_t *reg
) {
    if (!reg) return;
    for (size_t i = 0; i < reg->count; i++) {
        free(reg->paths[i]);
    }
    free(reg->paths);
    reg->paths = NULL;
    reg->count = 0;
    reg->cap = 0;
}

#endif

// Copyright (c) 2026 Zeronetsec