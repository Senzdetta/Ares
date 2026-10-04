// https://github.com/Zeronetsec/Ares

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "ares");
#include <missing_argument.h>
#include <invalid_option.h>

_Static_assert(1, "internal");
#include <render.h>
#include <list_themes.h>
#include <set_theme.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        missing_argument("yumipr");
        return EXIT_FAILURE;
    }

    if (
        strcmp(argv[1], "--render") == 0
    ) {
        render();
    } else if (
        strcmp(argv[1], "--list-themes") == 0
    ) {
        list_themes();
    } else if (
        strcmp(argv[1], "--settheme") == 0
    ) {
        if (argc < 3) {
            missing_argument("yumipr");
            return EXIT_FAILURE;
        }
        set_theme(argv[2]);
    } else {
        invalid_option(argv[1], "yumipr");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Copyright (c) 2026 Zeronetsec