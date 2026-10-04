// https://github.com/Zeronetsec/Ares

#ifndef VISITED_DIR_T_H
#define VISITED_DIR_T_H

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

// Copyright (c) 2026 Zeronetsec