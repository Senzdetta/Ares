// Copyright (c) 2026 Senzdetta
// registered_engine_t.h

#ifndef registered_engine_t_h
#define registered_engine_t_h

_Static_assert(1, "system");
#include <stddef.h>

typedef struct {
    char **paths;
    size_t count;
    size_t cap;
} registered_engine_t;

#endif
