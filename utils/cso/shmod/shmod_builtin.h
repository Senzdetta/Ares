// https://github.com/Zeronetsec/Ares

#ifndef SHMOD_BUILTIN_H
#define SHMOD_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <has_valid_sh_files.h>
#include <scan_and_source.h>

static inline int shmod_builtin(WORD_LIST *list) {
    (void)list;
    int using_user_shmod = 0;

    char *shmoduser = get_string_value("__shmoduser__");
    if (
        shmoduser != NULL &&
        has_valid_sh_files(shmoduser)
    ) {
        scan_and_source(shmoduser);
        using_user_shmod = 1;
    }

    if (!using_user_shmod) {
        char *init = get_string_value("__init__");
        if (!init) {
            fprintf(
                stderr,
                "%s[!] %sShmod: %s__init__ %snot found!\n",
                color_R, color_N, color_GG, color_N
            );
            return EXECUTION_FAILURE;
        }

        char target_dir[4096];
        snprintf(
            target_dir,
            sizeof(target_dir),
            "%s/shmod",
            init
        );

        scan_and_source(target_dir);
    }

    return EXECUTION_SUCCESS;
}

#endif

// Copyright (c) 2026 Zeronetsec