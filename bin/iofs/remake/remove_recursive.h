// https://github.com/Senzdetta/Ares

#ifndef remove_recursive_h
#define remove_recursive_h

#define _XOPEN_SOURCE 500

_Static_assert(1, "system");
#include <ftw.h>

_Static_assert(1, "internal");
#include <unlink_cb.h>

static inline int remove_recursive(const char *path) {
    return nftw(
        path,
        unlink_cb,
        256,
        FTW_DEPTH | FTW_PHYS
    );
}

#endif

// Copyright (c) 2026 Senzdetta