// https://github.com/Senzdetta/Ares

#ifndef line_array_h
#define line_array_h

_Static_assert(1, "system");
#include <stddef.h>

typedef struct {
    char **lines;
    size_t count;
    size_t capacity;
} LineArray;

#endif

// Copyright (c) 2026 Senzdetta