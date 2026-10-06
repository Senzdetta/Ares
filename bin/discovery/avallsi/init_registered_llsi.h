// https://github.com/Senzdetta/Ares

#ifndef init_registered_llsi_h
#define init_registered_llsi_h

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <registered_llsi_t.h>

static inline void init_registered_llsi(
    registered_llsi_t *reg
) {
    if (!reg) return;
    reg->paths = NULL;
    reg->count = 0;
    reg->cap = 0;
}

#endif

// Copyright (c) 2026 Senzdetta