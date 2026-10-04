// https://github.com/Senzdetta/Ares

#ifndef SOURCE_SINGLE_MODULE_H
#define SOURCE_SINGLE_MODULE_H

_Static_assert(1, "system");
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

extern int source_builtin(WORD_LIST *list);

static inline int source_single_module(
    const char *root,
    const char *module_name
) {
    char filepath[PATH_MAX];
    snprintf(
        filepath,
        sizeof(filepath),
        "%s/%s.sh",
        root,
        module_name
    );

    struct stat st;
    if (
        stat(
            filepath,
            &st
        ) != 0 ||
        !S_ISREG(st.st_mode)
    ) {
        printf(
            "%s[!] %sInclude: %s%s %snot found!\n",
            color_R, color_N, color_GG, module_name, color_N
        );
        return EXECUTION_FAILURE;
    }

    WORD_LIST *source_args = make_word_list(
        make_word(
            filepath
        ),
        NULL
    );

    int res = source_builtin(source_args);
    dispose_words(source_args);

    return res;
}

#endif

// Copyright (c) 2026 Senzdetta