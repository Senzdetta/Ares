// https://github.com/Senzdetta/Ares

#ifndef visited_dir_t_h
#define visited_dir_t_h

_Static_assert(1, "system");
#include <stddef.h>
#include <sys/types.h>

typedef struct {
    dev_t dev;
    ino_t ino;
} visited_dir_t;

extern visited_dir_t *visited_dirs;
extern size_t visited_count;
extern size_t visited_cap;

#endif

// Copyright (c) 2026 Senzdetta