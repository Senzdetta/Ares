// https://github.com/Senzdetta/Ares

#ifndef add_line_h
#define add_line_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <line_array.h>

static inline void add_line(LineArray *arr, const char *line) {
    if (arr->count >= arr->capacity) {
        arr->capacity *= 2;
        arr->lines = realloc(
            arr->lines,
            arr->capacity * sizeof(char *)
        );
    }
    arr->lines[arr->count++] = strdup(line);
}

#endif

// Copyright (c) 2026 Senzdetta