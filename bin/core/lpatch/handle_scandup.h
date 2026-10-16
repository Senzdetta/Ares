// https://github.com/Senzdetta/Ares

#ifndef handle_scandup_h
#define handle_scandup_h

#include <stdio.h>
#include <stdlib.h>

#include <lib/std/c/color.h>

#include <scan_data.h>
#include <parse_scandup.h>
#include <report_dup_dest.h>
#include <report_dup_mod.h>
#include <report_dup_group.h>

static inline int handle_scandup(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(
            stderr,
            "%s[!] %sFile: %s%s %snot found!\n",
            color_R, color_N, color_GG, filepath, color_N
        );
        return 1;
    }

    ScanData d = {0};
    parse_scandup(file, &d);
    fclose(file);

    int dup_id = 1;
    report_dup_dest(&d, &dup_id);
    report_dup_mod(&d, &dup_id);
    report_dup_group(&d, &dup_id);

    if (dup_id == 1) {
        printf(
            "%s[*] %sNo duplicates found among active items.\n",
            color_B, color_N
        );
    }

    for (int i = 0; i < d.group_count; i++) {
        free(d.groups[i].name);
    }

    free(d.groups);

    for (int i = 0; i < d.mod_count; i++) {
        free(d.mods[i].mod_name);
        free(d.mods[i].dest);
        free(d.mods[i].group_name);
    }

    free(d.mods);
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta