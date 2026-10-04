// https://github.com/Zeronetsec/Ares

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "ares");
#include <color.h>
#include <missing_argument.h>

_Static_assert(1, "internal");
#include <apply_cursor_style.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        missing_argument("setcursor");
        return 1;
    }

    if (apply_cursor_style(argv[1]) != 0) {
        fprintf(
            stderr,
            "%s[!] %sStyle: %s%s %snot available!\n",
            color_R, color_N, color_GG, argv[1], color_N
        );
        return 1;
    }

    return 0;
}

// Copyright (c) 2026 Zeronetsec