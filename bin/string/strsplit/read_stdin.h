// https://github.com/Senzdetta/Ares

#ifndef read_stdin_h
#define read_stdin_h

#include <stdio.h>
#include <stdlib.h>

static inline char* read_stdin(void) {
    size_t size = 1024;
    size_t len = 0;

    char *buffer = malloc(size);
    if (!buffer) {
        return NULL;
    }

    int c;
    while ((c = getchar()) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[len++] = (char)c;
    }

    buffer[len] = '\0';
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

#endif

// Copyright (c) 2026 Senzdetta