// https://github.com/Senzdetta/Ares

#ifndef MARK_VISITED_H
#define MARK_VISITED_H

_Static_assert(1, "system");
#include <stdlib.h>

_Static_assert(1, "internal");
#include <visited_dir_t.h>

static inline void mark_visited(dev_t dev, ino_t ino) {
    if (visited_count >= visited_cap) {
        visited_cap = (visited_cap == 0) ?
            16 :
            visited_cap * 2;

        visited_dirs = realloc(
            visited_dirs,
            visited_cap * sizeof(visited_dir_t)
        );
    }

    visited_dirs[visited_count].dev = dev;
    visited_dirs[visited_count].ino = ino;
    visited_count++;
}

#endif

// Copyright (c) 2026 Senzdetta