// https://github.com/Zeronetsec/Ares

#ifndef GET_PATH_COLOR_H
#define GET_PATH_COLOR_H

_Static_assert(1, "system");
#include <string.h>

static inline const char* get_path_color(const char *pwd) {
    if (
        strcmp(pwd, "/") == 0 ||
        strncmp(pwd, "/root", 5) == 0
    ) {
        return "\001\x1b[0;31m\002";
    } else if (
        strncmp(pwd, "/etc", 4) == 0
    ) {
        return "\001\x1b[0;32m\002";
    } else if (
        strncmp(pwd, "/usr", 4) == 0
    ) {
        return "\001\x1b[0;34m\002";
    }
    return "\001\x1b[0;33m\002";
}

#endif

// Copyright (c) 2026 Zeronetsec