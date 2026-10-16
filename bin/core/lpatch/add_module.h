// https://github.com/Senzdetta/Ares

#ifndef add_module_h
#define add_module_h

#include <stdlib.h>
#include <string.h>

#include <group.h>
#include <module.h>

static inline int add_module(
    Group *g,
    char *raw_line,
    const char *name,
    int is_disabled
) {
    if (g->mod_count >= g->mod_capacity) {
        int new_cap = g->mod_capacity * 2;
        Module *tmp = realloc(
            g->mods,
            new_cap * sizeof(Module)
        );

        if (!tmp) {
            free(raw_line);
            return 1;
        }

        g->mods = tmp;
        g->mod_capacity = new_cap;
    }

    Module *m = &g->mods[g->mod_count];
    m->raw_line = raw_line;
    m->name = strdup(name);
    m->is_disabled = is_disabled;
    g->mod_count++;

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta