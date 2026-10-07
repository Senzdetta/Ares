// https://github.com/Senzdetta/Ares

#ifndef utils_banner_h
#define utils_banner_h

#include <stdio.h>
#include <utils/color.h>
#include <utils/embeded_banner.h>

static inline void banner(void) {
    printf(
        "%s%s%s\n\n",
        color_B, embeded_banner, color_N
    );
}

#endif

// Copyright (c) 2026 Senzdetta