// https://github.com/Senzdetta/Ares

#ifndef set_theme_h
#define set_theme_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>

_Static_assert(1, "internal");
#include <get_config.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline void set_theme(const char *new_theme) {
    char config_path[MAX_PATH];
    get_config(config_path, sizeof(config_path));

    FILE *f = fopen(config_path, "w");
    if (!f) {
        perror("failed to write config");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "yumipr_theme = %s\n", new_theme);
    fclose(f);
}

#endif

// Copyright (c) 2026 Senzdetta