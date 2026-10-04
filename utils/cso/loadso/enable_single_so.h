// https://github.com/Senzdetta/Ares

#ifndef ENABLE_SINGLE_SO_H
#define ENABLE_SINGLE_SO_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

extern int enable_builtin(WORD_LIST *list);

static inline int enable_single_so(
    const char *root,
    char *line
) {
    char *module_path = line;
    char *builtin_name = NULL;
    char *arrow = strstr(line, "->");

    if (arrow != NULL) {
        *arrow = '\0';
        builtin_name = arrow + 2;

        char *end_path = arrow - 1;
        while (
            end_path >= module_path &&
            isspace((unsigned char)*end_path)
        ) {
            *end_path = '\0';
            end_path--;
        }

        while (isspace((unsigned char)*builtin_name)) {
            builtin_name++;
        }
    } else {
        builtin_name = strrchr(
            module_path,
            '/'
        );
        if (builtin_name != NULL) {
            builtin_name++;
        } else {
            builtin_name = module_path;
        }
    }

    if (
        *module_path == '\0' ||
        *builtin_name == '\0'
    ) {
        printf(
            "%s[!] %sInvalid syntax!\n",
            color_R, color_N
        );
        return EXECUTION_FAILURE;
    }

    char filepath[PATH_MAX];
    snprintf(
        filepath,
        sizeof(filepath),
        "%s/%s.so",
        root,
        module_path
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
            "%s[!] %sLoadso: %s%s %snot found!\n",
            color_R, color_N, color_GG, module_path, color_N
        );
        return EXECUTION_FAILURE;
    }

    WORD_LIST *arg_name = make_word_list(
        make_word(builtin_name),
        NULL
    );

    WORD_LIST *arg_path = make_word_list(
        make_word(filepath),
        arg_name
    );

    WORD_LIST *enable_args = make_word_list(
        make_word("-f"),
        arg_path
    );

    int res = enable_builtin(enable_args);
    dispose_words(enable_args);

    return res;
}

#endif

// Copyright (c) 2026 Senzdetta