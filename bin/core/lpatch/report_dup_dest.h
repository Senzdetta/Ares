// https://github.com/Senzdetta/Ares

#ifndef report_dup_dest_h
#define report_dup_dest_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/std/c/color.h>

#include <scan_data.h>

static inline void report_dup_dest(
    const ScanData *d,
    int *dup_id
) {
    int *visited = calloc(
        d->mod_count, sizeof(int)
    );

    int *matches = malloc(
        d->mod_count * sizeof(int)
    );

    for (int i = 0; i < d->mod_count; i++) {
        if (visited[i]) {
            continue;
        }

        int match_count = 0;
        matches[match_count++] = i;

        for (int j = i + 1; j < d->mod_count; j++) {
            if (
                !visited[j] &&
                strcmp(
                    d->mods[i].dest,
                    d->mods[j].dest
                ) == 0
            ) {
                matches[match_count++] = j;
            }
        }

        if (match_count < 2) {
            continue;
        }

        printf(
            "%s› %sdupscan: %s%d%s\n",
            color_R, color_N, color_GG, (*dup_id)++, color_N
        );

        for (int k = 0; k < match_count; k++) {
            const ScanMod *m = &d->mods[matches[k]];
            visited[matches[k]] = 1;
            printf(
                "  %s› %sllsi: %s%s %sfrom mod %s%s %sfrom group %s%s %s(%sline: %s%d%s)%s\n",
                color_B,
                color_N, color_GG, m->dest,
                color_N, color_GG, m->mod_name,
                color_N, color_GG, m->group_name,
                color_DG, color_WW, color_CC, m->line_no, color_DG,
                color_N
            );
        }
    }

    free(matches);
    free(visited);
}

#endif

// Copyright (c) 2026 Senzdetta