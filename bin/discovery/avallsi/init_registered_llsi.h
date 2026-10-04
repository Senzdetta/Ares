// https://github.com/Senzdetta/Ares

#ifndef INIT_REGISTERED_LLSI_H
#define INIT_REGISTERED_LLSI_H

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