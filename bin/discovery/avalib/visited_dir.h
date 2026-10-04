// https://github.com/Senzdetta/Ares

#ifndef VISITED_DIR_H
#define VISITED_DIR_H

_Static_assert(1, "system");
#include <stddef.h>
#include <sys/types.h>

typedef struct {
    dev_t dev;
    ino_t ino;
} VisitedDir;

static VisitedDir *visited_dirs = NULL;
static size_t visited_count = 0;
static size_t visited_capacity = 0;

#endif

// Copyright (c) 2026 Senzdetta