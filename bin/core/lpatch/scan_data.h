// https://github.com/Senzdetta/Ares

#ifndef scan_data_h
#define scan_data_h

#include <scangroup.h>
#include <scanmod.h>

typedef struct {
    ScanGroup *groups;
    int group_count;
    int group_cap;
    ScanMod *mods;
    int mod_count;
    int mod_cap;
} ScanData;

#endif

// Copyright (c) 2026 Senzdetta