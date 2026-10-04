// https://github.com/Senzdetta/Ares

#ifndef CURSOR_STYLES_H
#define CURSOR_STYLES_H

_Static_assert(1, "system");
#include <stddef.h>

_Static_assert(1, "internal");
#include <cursor_option.h>
#include <const_style.h>

static const CursorOption CURSOR_STYLES[] = {
    {"default", STYLE_DEFAULT},
    {"blink-block", STYLE_BLINK_BLOCK},
    {"block", STYLE_BLOCK},
    {"blink-underline", STYLE_BLINK_UNDERLINE},
    {"underline", STYLE_UNDERLINE},
    {"blink-line", STYLE_BLINK_LINE},
    {"line", STYLE_LINE}
};

static const size_t TOTAL_STYLES = sizeof(
    CURSOR_STYLES
) / sizeof(
    CURSOR_STYLES[0]
);

#endif

// Copyright (c) 2026 Senzdetta