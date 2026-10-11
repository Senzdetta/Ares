// https://github.com/Senzdetta/Ares

#ifndef batch_junk_h
#define batch_junk_h

#include <stdlib.h>
#include <string.h>
#include <junk_item.h>

static inline void batch_junk(const char *batch_str) {
    char *buffer = strdup(batch_str);
    char *token = strtok(buffer, ",");

    while (token != NULL) {
        junk_item(token);
        token = strtok(NULL, ",");
    }

    free(buffer);
}

#endif

// Copyright (c) 2026 Senzdetta