// https://github.com/Senzdetta/Ares

#ifndef load_exclusions_file_h
#define load_exclusions_file_h

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "internal");
#include <add_exclude_rule.h>
#include <exclude_list.h>

static inline void load_exclusions_file(
    const char *filepath,
    ExcludeList *list
) {
    if (!filepath || !*filepath) {
        return;
    }

    FILE *fp = fopen(filepath, "r");
    if (!fp) return;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        add_exclude_rule(list, line);
    }
    fclose(fp);
}

#endif

// Copyright (c) 2026 Senzdetta