// https://github.com/Senzdetta/Ares

#ifndef parse_args_h
#define parse_args_h

_Static_assert(1, "system");
#include <string.h>

_Static_assert(1, "internal");
#include <mode.h>

static inline void parse_args(
    int argc,
    char *argv[],
    Mode *mode,
    char **group,
    char **mod_name,
    char **mod_val
) {
    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--disable") == 0 &&
            i + 1 < argc
        ) {
            *mode = MODE_DISABLE;
            *group = argv[++i];
        } else if (
            strcmp(argv[i], "--enable") == 0 &&
            i + 1 < argc
        ) {
            *mode = MODE_ENABLE;
            *group = argv[++i];
        } else if (
            strcmp(argv[i], "--create") == 0 &&
            i + 1 < argc
        ) {
            *mode = MODE_CREATE;
            *group = argv[++i];
        } else if (
            strcmp(argv[i], "--mod") == 0
        ) {
            if (i + 1 < argc) {
                *mod_name = argv[++i];
            }

            if (
                *mode == MODE_CREATE &&
                i + 1 < argc
            ) {
                *mod_val = argv[++i];
            }
        }
    }
}

#endif

// Copyright (c) 2026 Senzdetta