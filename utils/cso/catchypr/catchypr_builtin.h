// https://github.com/Senzdetta/Ares

#ifndef catchypr_builtin_h
#define catchypr_builtin_h

_Static_assert(1, "system");
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

_Static_assert(1, "internal");
#include <get_formatted_path.h>
#include <get_path_color.h>
#include <get_time_symbol.h>

static inline int catchypr_builtin(WORD_LIST *list) {
    char *exit_str = get_string_value("exit_code");
    int exit_code = exit_str ?
        atoi(exit_str) :
        0;

    char *pwd = get_string_value("PWD");
    if (!pwd) pwd = "/";

    char *home = get_string_value("HOME");

    char *dirtrim_str = get_string_value("PROMPT_DIRTRIM");
    int dirtrim = dirtrim_str ?
        atoi(dirtrim_str) :
        0;

    char cpath[2048];
    get_formatted_path(
        pwd, home, dirtrim,
        cpath, sizeof(cpath)
    );

    const char *path_color = get_path_color(pwd);
    const char *symbol1 = get_time_symbol();
    const char *sss = (geteuid() == 0) ?
        "#" :
        "$";

    char symbol2[128];
    char symbol3[128];

    if (exit_code == 0) {
        snprintf(
            symbol2,
            sizeof(symbol2),
            "\001\x1b[38;5;244m\002%s",
            symbol1
        );
        snprintf(
            symbol3,
            sizeof(symbol3),
            "\001\x1b[38;5;252m\002%s",
            sss
        );
    } else {
        snprintf(
            symbol2,
            sizeof(symbol2),
            "\001\x1b[1;34m\002%s",
            symbol1
        );
        snprintf(
            symbol3,
            sizeof(symbol3),
            "\001\x1b[1;31m\002%s",
            sss
        );
    }
    printf(
        "\001\x1b[?25h\002\n"
        "\001\x1b[38;5;244m\002┌──(\001\x1b[1;31m\002Ares\001\x1b[38;5;244m\002(%s\001\x1b[38;5;244m\002)\001\x1b[1;31m\002Framework\001\x1b[38;5;244m\002)-(%s%s\001\x1b[38;5;244m\002)\n"
        "\001\x1b[38;5;244m\002└──%s\001\x1b[0m\002 ", 
        symbol2, path_color, cpath, symbol3
    );
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta