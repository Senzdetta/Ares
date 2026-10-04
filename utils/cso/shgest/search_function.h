// https://github.com/Zeronetsec/Ares

#ifndef SEARCH_FUNCTION_H
#define SEARCH_FUNCTION_H

_Static_assert(1, "system");
#include <string.h>
#include <stdlib.h>

extern SHELL_VAR **all_shell_functions (void);

static inline char *search_function(
    const char *input,
    size_t len
) {
    const char *last_word = strrchr(input, ' ');
    if (last_word) {
        last_word++;
    } else {
        last_word = input;
    }

    size_t wlen = strlen(last_word);
    if (wlen == 0) {
        return NULL;
    }

    SHELL_VAR **funcs = all_shell_functions();
    if (!funcs) {
        return NULL;
    }

    char *res = NULL;
    for (int i = 0; funcs[i]; i++) {
        if (
            funcs[i]->name &&
            strncmp(funcs[i]->name, last_word, wlen) == 0
        ) {
            if (strlen(funcs[i]->name) > wlen) {
                size_t prefix_len = last_word - input;
                size_t full_len = prefix_len +
                    strlen(funcs[i]->name) +
                    1;

                res = malloc(full_len);
                if (res) {
                    strncpy(res, input, prefix_len);
                    res[prefix_len] = '\0';
                    strcat(res, funcs[i]->name);
                }
                break;
            }
        }
    }
    free(funcs);
    return res;
}

#endif

// Copyright (c) 2026 Zeronetsec