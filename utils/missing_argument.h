// https://github.com/Zeronetsec/Ares

#ifndef utils_missing_argument_h
#define utils_missing_argument_h

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "internal");
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

// Copyright (c) 2026 Zeronetsec