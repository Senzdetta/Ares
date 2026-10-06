// https://github.com/Senzdetta/Ares

#ifndef free_array_h
#define free_array_h

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <line_array.h>

static inline void free_array(LineArray *arr) {
    for (size_t i = 0; i < arr->count; i++) {
        free(arr->lines[i]);
    }
    free(arr->lines);
}

#endif

// Copyright (c) 2026 Senzdetta