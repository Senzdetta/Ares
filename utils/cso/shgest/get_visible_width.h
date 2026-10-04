// https://github.com/Senzdetta/Ares

#ifndef GET_VISIBLE_WIDTH_H
#define GET_VISIBLE_WIDTH_H

_Static_assert(1, "system");
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

static inline int get_visible_width(const char *str) {
    if (!str) {
        return 0;
    }

    setlocale(LC_CTYPE, "");

    int width = 0;
    int in_esc = 0;

    mbstate_t state = {0};

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (str[i] == '\x1b') {
            in_esc = 1;
            i++;
            continue;
        }
        
        if (in_esc) {
            if (isalpha((unsigned char)str[i])) {
                in_esc = 0;
            }
            i++;
            continue;
        }

        if (str[i] == '\001' || str[i] == '\002') {
            i++;
            continue;
        }

        wchar_t wc;
        size_t bytes = mbrtowc(
            &wc,
            str + i,
            len - i,
            &state
        );

        if (bytes == (size_t)-1 || bytes == (size_t)-2) {
            width++;
            i++;
            memset(
                &state,
                0,
                sizeof(state)
            );
        } else if (bytes == 0) {
            break;
        } else {
            int w = wcwidth(wc);
            if (w > 0) {
                width += w;
            }
            i += bytes;
        }
    }
    return width;
}

#endif

// Copyright (c) 2026 Senzdetta