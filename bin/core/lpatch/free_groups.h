// https://github.com/Senzdetta/Ares    

#ifndef free_groups_h
#define free_groups_h

#include <stdlib.h>

#include <group.h>

static inline void free_groups(Group *groups, int group_count) {
    for (int i = 0; i < group_count; i++) {
        free(groups[i].name);
        for (int j = 0; j < groups[i].mod_count; j++) {
            free(groups[i].mods[j].raw_line);
            free(groups[i].mods[j].name);
        }
        free(groups[i].mods);
    }
    free(groups);
}

#endif

// Copyright (c) 2026 Senzdetta