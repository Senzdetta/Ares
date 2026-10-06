// https://github.com/Senzdetta/Ares

#ifndef registered_llsi_t_h
#define registered_llsi_t_h

_Static_assert(1, "system");
#include <stddef.h>

typedef struct {
    char **paths;
    size_t count;
    size_t cap;
} registered_llsi_t;

#endif

// Copyright (c) 2026 Senzdetta