// https://github.com/Senzdetta/Ares

#ifndef add_group_h
#define add_group_h

#include <stdlib.h>

#include <group.h>
#include <module.h>

static inline Group *add_group(
    Group **groups,
    int *count,
    int *cap,
    char *name,
    int is_disabled
) {
    if (*count >= *cap) {
        int new_cap = *cap * 2;
        Group *tmp = realloc(
            *groups,
            new_cap * sizeof(Group)
        );

        if (!tmp) {
            free(name);
            return NULL;
        }

        *groups = tmp;
        *cap = new_cap;
    }

    Group *g = &(*groups)[*count];
    g->mod_capacity = 10;
    g->mods = malloc(
        g->mod_capacity * sizeof(Module)
    );

    if (!g->mods) {
        free(name);
        return NULL;
    }

    g->name = name;
    g->is_disabled = is_disabled;
    g->mod_count = 0;

    (*count)++;
    return g;
}

#endif

// Copyright (c) 2026 Senzdetta