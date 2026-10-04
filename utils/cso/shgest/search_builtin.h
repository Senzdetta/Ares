// https://github.com/Zeronetsec/Ares

#ifndef SEARCH_BUILTIN_H
#define SEARCH_BUILTIN_H

_Static_assert(1, "system");
#include <string.h>
#include <stdlib.h>

static inline char *search_builtin(
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

    for (int i = 0; i < num_shell_builtins; i++) {
        if (
            shell_builtins[i].name &&
            strncmp(shell_builtins[i].name, last_word, wlen) == 0
        ) {
            if (strlen(shell_builtins[i].name) > wlen) {
                size_t prefix_len = last_word - input;
                size_t full_len = prefix_len +
                    strlen(shell_builtins[i].name) +
                    1;

                char *res = malloc(full_len);
                if (res) {
                    strncpy(res, input, prefix_len);
                    res[prefix_len] = '\0';
                    strcat(res, shell_builtins[i].name);
                }
                return res;
            }
        }
    }
    return NULL;
}

#endif

// Copyright (c) 2026 Zeronetsec