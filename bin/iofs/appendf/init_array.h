// https://github.com/Senzdetta/Ares

#ifndef init_array_h
#define init_array_h

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <line_array.h>

static inline void init_array(LineArray *arr) {
    arr->capacity = 1024;
    arr->count = 0;
    arr->lines = malloc(
        arr->capacity * sizeof(char *)
    );
}

#endif

// Copyright (c) 2026 Senzdetta