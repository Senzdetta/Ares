// https://github.com/Zeronetsec/Ares

#ifndef REGISTERED_LLSI_T_H
#define REGISTERED_LLSI_T_H

_Static_assert(1, "system");
#include <stddef.h>

typedef struct {
    char **paths;
    size_t count;
    size_t cap;
} registered_llsi_t;

#endif

// Copyright (c) 2026 Zeronetsec