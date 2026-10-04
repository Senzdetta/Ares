// https://github.com/Senzdetta/Ares

#ifndef utils_birthday_h
#define utils_birthday_h

_Static_assert(1, "system");
#include <stdio.h>
#include <time.h>

_Static_assert(1, "internal");
#include <utils/color.h>

static inline void birthday(void) {
    time_t t = time(NULL);
    struct tm tm_info = *localtime(&t);
    if (tm_info.tm_mon == 7 && tm_info.tm_mday == 23) {
        printf(
            "%s› %sHappy birthday for %sAres %s🎉\n\n",
            color_R, color_N, color_GG, color_N
        );
    }
}

#endif

// Copyright (c) 2026 Senzdetta