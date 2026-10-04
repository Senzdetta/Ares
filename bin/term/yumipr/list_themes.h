// https://github.com/Senzdetta/Ares

#ifndef LIST_THEMES_H
#define LIST_THEMES_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

_Static_assert(1, "internal");
#include <get_themes.h>
#include <scan_recursive.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline void list_themes(void) {
    char themes_dir[MAX_PATH];
    get_themes(themes_dir, sizeof(themes_dir));

    DIR *d = opendir(themes_dir);
    if (!d) {
        perror("failed to open themes directory");
        exit(EXIT_FAILURE);
    }
    closedir(d);

    scan_recursive(themes_dir, "");
}

#endif

// Copyright (c) 2026 Senzdetta