// https://github.com/Senzdetta/Ares

#ifndef SEARCH_HISTORY_H
#define SEARCH_HISTORY_H

_Static_assert(1, "system");
#include <string.h>

static inline char *search_history(
    const char *input,
    size_t len
) {
    HIST_ENTRY **hist_list = history_list();
    if (!hist_list) {
        return NULL;
    }

    for (int i = history_length - 1; i >= 0; i--) {
        if (
            hist_list[i] &&
            strncmp(hist_list[i]->line, input, len) == 0
        ) {
            if (strlen(hist_list[i]->line) > len) {
                return strdup(hist_list[i]->line);
            }
        }
    }
    return NULL;
}

#endif

// Copyright (c) 2026 Senzdetta