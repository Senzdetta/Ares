// https://github.com/Senzdetta/Ares

#ifndef group_h
#define group_h

#include <module.h>

typedef struct {
    char *name;
    int is_disabled;
    Module *mods;
    int mod_count;
    int mod_capacity;
} Group;

#endif

// Copyright (c) 2026 Senzdetta