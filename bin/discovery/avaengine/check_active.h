// https://github.com/Senzdetta/Ares

#ifndef check_active_h
#define check_active_h

#include <string.h>

#include <active_engine.h>

static inline int check_active(
    const char *base_trim,
    const char *current_dir,
    const char *filename,
    int show_active,
    const ActiveEngine *active_engines,
    int active_count
) {
    if (!show_active) {
        return 0;
    }

    const char *rel_path = current_dir;
    if (
        strncmp(
            current_dir, base_trim,
            strlen(base_trim)
        ) == 0
    ) {
        rel_path = current_dir + strlen(base_trim);
        if (rel_path[0] == '/') {
            rel_path++;
        }
    }

    for (int i = 0; i < active_count; i++) {
        if (
            strstr(
                rel_path,
                active_engines[i].category
            ) != NULL &&
            strcmp(filename, active_engines[i].name) == 0
        ) {
            return 1;
        }
    }

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta