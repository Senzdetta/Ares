// https://github.com/Zeronetsec/Ares

#ifndef SEARCH_ALIAS_H
#define SEARCH_ALIAS_H

_Static_assert(1, "system");
#include <string.h>
#include <stdlib.h>

extern alias_t **all_aliases (void);

static inline char *search_alias(
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

    alias_t **aliases = all_aliases();
    if (!aliases) {
        return NULL;
    }

    char *res = NULL;
    for (int i = 0; aliases[i]; i++) {
        if (
            aliases[i]->name &&
            strncmp(aliases[i]->name, last_word, wlen) == 0
        ) {
            if (strlen(aliases[i]->name) > wlen) {
                size_t prefix_len = last_word - input;
                size_t full_len = prefix_len +
                    strlen(aliases[i]->name) +
                    1;

                res = malloc(full_len);
                if (res) {
                    strncpy(res, input, prefix_len);
                    res[prefix_len] = '\0';
                    strcat(res, aliases[i]->name);
                }
                break;
            }
        }
    }
    free(aliases);
    return res;
}

#endif

// Copyright (c) 2026 Zeronetsec