// https://github.com/Senzdetta/Ares

#ifndef utils_missing_argument_h
#define utils_missing_argument_h

#include <stdio.h>
#include <utils/color.h>

static inline void missingArgument(void) {
    printf(
        "%s[!] %sMissing argument!\n",
        color_R, color_N
    );

    printf(
        "%s[!] %sTry: %sares --help%s\n",
        color_R, color_N, color_GG, color_N
    );
}

#endif

// Copyright (c) 2026 Senzdetta