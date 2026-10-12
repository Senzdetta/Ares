// https://github.com/Senzdetta/Ares

#ifndef print_colored_suffix_h
#define print_colored_suffix_h

_Static_assert(1, "system");
#include <ctype.h>
#include <stdio.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <shgest_state.h>

static inline void print_colored_suffix(const char *suffix) {
    const char *primary_color = color_DG;
    if (
        last_matched_source != SRC_COUNT &&
        source_colors[last_matched_source][0] != '\0'
    ) {
        primary_color = source_colors[last_matched_source];
    }

    for (int i = 0; suffix[i] != '\0'; i++) {
        char c = suffix[i];
        if (isalnum((unsigned char)c)) {
            printf(
                "%s%c",
                primary_color, c
            );
        } else {
            printf(
                "%s%c",
                other_color[0] ?
                    other_color :
                    "\x1b[38;5;245m",
                c
            );
        }
    }
    printf(
        "%s",
        color_N
    );
}

#endif

// Copyright (c) 2026 Senzdetta