// https://github.com/Senzdetta/Ares

#ifndef EXCLUDE_LIST_H
#define EXCLUDE_LIST_H

_Static_assert(1, "system");
#include <stddef.h>

typedef struct {
    char **rules;
    size_t count;
    size_t capacity;
} ExcludeList;

#endif

// Copyright (c) 2026 Senzdetta