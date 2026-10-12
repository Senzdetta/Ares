// Copyright (c) 2026 Senzdetta
// init_registered_engine.h

#ifndef init_registered_engine_h
#define init_registered_engine_h

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <registered_engine_t.h>

static inline void init_registered_engine(
    registered_engine_t *reg
) {
    if (!reg) return;
    reg->paths = NULL;
    reg->count = 0;
    reg->cap = 0;
}

#endif
