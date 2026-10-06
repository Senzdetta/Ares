// https://github.com/Senzdetta/Ares

#ifndef validate_input_h
#define validate_input_h

_Static_assert(1, "system");
#include <string.h>

static inline char *validate_input(WORD_LIST *list) {
    if (
        !list ||
        !list->word ||
        !list->word->word ||
        strcmp(list->word->word, ":") != 0
    ) {
        return NULL;
    }

    list = list->next;
    if (
        !list ||
        !list->word ||
        !list->word->word ||
        list->word->word[0] == '\0'
    ) {
        return NULL;
    }

    return list->word->word;
}

#endif

// Copyright (c) 2026 Senzdetta