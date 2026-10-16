// https://github.com/Senzdetta/Ares

#ifndef add_scan_group_h
#define add_scan_group_h

#include <stdlib.h>
#include <string.h>

#include <scan_data.h>

static inline void add_scan_group(
    ScanData *d,
    const char *name,
    int line_no
) {
    if (d->group_count >= d->group_cap) {
        d->group_cap = d->group_cap ?
            d->group_cap * 2 :
            10;

        d->groups = realloc(
            d->groups,
            d->group_cap * sizeof(ScanGroup)
        );
    }

    d->groups[d->group_count].name = strdup(name);
    d->groups[d->group_count].line_no = line_no;
    d->group_count++;
}

#endif

// Copyright (c) 2026 Senzdetta