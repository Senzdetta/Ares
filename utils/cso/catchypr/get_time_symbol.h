// https://github.com/Senzdetta/Ares

#ifndef get_time_symbol_h
#define get_time_symbol_h

_Static_assert(1, "system");
#include <time.h>

static inline const char* get_time_symbol(void) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    switch (tm_info->tm_hour) {
        case 0: return "☾";
        case 1: return "⋄";
        case 5: return "⚔";
        case 7: return "✈︎";
        case 12: return "𓃵";
        case 20: return "𖤐";
        default: return "𖤍";
    }
}

#endif

// Copyright (c) 2026 Senzdetta