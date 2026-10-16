// https://github.com/Senzdetta/Ares

#ifndef add_scan_mod_h
#define add_scan_mod_h

#include <stdlib.h>
#include <string.h>

#include <scan_data.h>

static inline void add_scan_mod(
    ScanData *d,
    const char *mod_name,
    const char *dest,
    const char *group_name,
    int line_no
) {
    if (d->mod_count >= d->mod_cap) {
        d->mod_cap = d->mod_cap ?
            d->mod_cap * 2 :
            20;

        d->mods = realloc(
            d->mods,
            d->mod_cap * sizeof(ScanMod)
        );
    }

    ScanMod *m = &d->mods[d->mod_count];
    m->mod_name = strdup(mod_name);
    m->dest = strdup(dest);
    m->group_name = strdup(group_name);
    m->line_no = line_no;
    d->mod_count++;
}

#endif

// Copyright (c) 2026 Senzdetta