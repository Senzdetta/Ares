// https://github.com/Senzdetta/Ares

#ifndef add_registered_path_h
#define add_registered_path_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <registered_llsi_t.h>

static inline void add_registered_path(
    registered_llsi_t *reg,
    const char *path
) {
    if (!reg || !path) return;
    if (reg->count >= reg->cap) {
        reg->cap = (reg->cap == 0) ?
            16 :
            reg->cap * 2;
        reg->paths = realloc(
            reg->paths,
            reg->cap * sizeof(char *)
        );
    }
    reg->paths[reg->count++] = strdup(path);
}

#endif

// Copyright (c) 2026 Senzdetta