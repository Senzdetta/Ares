// https://github.com/Senzdetta/Ares

#ifndef exist_mode_h
#define exist_mode_h

#include <sys/stat.h>

static inline mode_t exist_mode(const char *path) {
    struct stat st;
    if (lstat(path, &st) == 0) {
        return st.st_mode & 07777;
    }
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta