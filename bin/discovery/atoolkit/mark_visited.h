// https://github.com/Senzdetta/Ares

#ifndef mark_visited_h
#define mark_visited_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <sys/types.h>

_Static_assert(1, "internal");
#include <visited_dir.h>

static inline void mark_visited(dev_t dev, ino_t ino) {
    if (visited_count >= visited_capacity) {
        visited_capacity = visited_capacity == 0 ?
            16 :
            visited_capacity * 2;

        visited_dirs = realloc(
            visited_dirs,
            visited_capacity * sizeof(VisitedDir)
        );
    }

    visited_dirs[visited_count].dev = dev;
    visited_dirs[visited_count].ino = ino;

    visited_count++;
}

#endif

// Copyright (c) 2026 Senzdetta