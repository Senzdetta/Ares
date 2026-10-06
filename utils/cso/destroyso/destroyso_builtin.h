// https://github.com/Senzdetta/Ares

#ifndef destroyso_builtin_h
#define destroyso_builtin_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <process_destroy_lines.h>

static inline int destroyso_builtin(WORD_LIST *list) {
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
        !list->word->word ||
        list->word->word[0] == '\0'
    ) {
        return EXECUTION_FAILURE;
    }

    char *input_data = list->word->word;
    char *data_copy = strdup(input_data);
    if (!data_copy) {
        return EXECUTION_FAILURE;
    }

    int final_status = process_destroy_lines(data_copy);

    free(data_copy);
    return final_status;
}

#endif

// Copyright (c) 2026 Senzdetta