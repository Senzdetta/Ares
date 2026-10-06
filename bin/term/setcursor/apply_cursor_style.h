// https://github.com/Senzdetta/Ares

#ifndef apply_cursor_style_h
#define apply_cursor_style_h

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>

_Static_assert(1, "internal");
#include <cursor_styles.h>

static inline int apply_cursor_style(const char *style_name) {
    for (size_t i = 0; i < TOTAL_STYLES; i++) {
        if (strcmp(style_name, CURSOR_STYLES[i].name) == 0) {
            printf(
                "%s",
                CURSOR_STYLES[i].code
            );
            return 0;
        }
    }
    return -1;
}

#endif

// Copyright (c) 2026 Senzdetta