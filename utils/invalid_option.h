// https://github.com/Zeronetsec/Ares

#ifndef utils_invalid_option_h
#define utils_invalid_option_h

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "internal");
#include <utils/color.h>

static inline void invalidOption(const char *input) {
    printf(
        "%s[!] %sInvalid option: %s%s%s\n",
        color_R, color_N, color_GG,
        input ? input : "",
        color_N
    );

    printf(
        "%s[!] %sTry: %sares --help%s\n",
        color_R, color_N, color_GG, color_N
    );
}

#endif

// Copyright (c) 2026 Zeronetsec