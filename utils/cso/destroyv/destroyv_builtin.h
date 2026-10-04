// https://github.com/Senzdetta/Ares

#ifndef DESTROYV_BUILTIN_H
#define DESTROYV_BUILTIN_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <process_destroy_lines.h>

static inline int destroyv_builtin(WORD_LIST *list) {
    if (
        !list ||
        !list->word ||
        !list->word->word ||
        strcmp(list->word->word, ":") != 0
    ) {
        return EXECUTION_FAILURE;
    }

    list = list->next;
    if (
        !list ||
        !list->word ||
        !list->word->word
    ) {
        return EXECUTION_FAILURE;
    }

    char *input_data = list->word->word;
    if (input_data[0] == '\0') {
        return EXECUTION_FAILURE;
    }

    char *data_copy = strdup(input_data);
    if (!data_copy) {
        return EXECUTION_FAILURE;
    }

    process_destroy_lines(data_copy);

    free(data_copy);
    return EXECUTION_SUCCESS;
}

#endif

// Copyright (c) 2026 Senzdetta