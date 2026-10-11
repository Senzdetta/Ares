// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unescape_string.h>
#include <read_stdin.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    const char *target_chars = NULL;
    const char *input_str = NULL;
    const char *raw_transform = NULL;

    int use_stdin = 0;

    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--char") == 0 &&
            (i + 1) < argc
        ) {
            target_chars = argv[++i];
        } else if (
            strcmp(argv[i], "--str") == 0 &&
            (i + 1) < argc
        ) {
            input_str = argv[++i];
        } else if (
            strcmp(argv[i], "--stdin") == 0
        ) {
            use_stdin = 1;
        } else if (
            strcmp(argv[i], "--transform") == 0 &&
            (i + 1) < argc
        ) {
            raw_transform = argv[++i];
        }
    }

    if (!target_chars) {
        return 0;
    }

    char *allocated_input = NULL;
    if (use_stdin) {
        allocated_input = read_stdin();
        input_str = allocated_input;
    }

    if (!input_str) {
        if (allocated_input) {
            free(allocated_input);
        }
        return 0;
    }

    char *transform_str = unescape_string(raw_transform);
    int input_len = strlen(input_str);

    for (int i = 0; i < input_len; i++) {
        char c = input_str[i];

        if (strchr(target_chars, c) != NULL) {
            if (transform_str != NULL) {
                printf(
                    "%s",
                    transform_str
                );
            }
        } else {
            putchar(c);
        }
    }

    if (allocated_input) {
        free(allocated_input);
    }

    if (transform_str) {
        free(transform_str);
    }

    return 0;
}

// Copyright (c) 2026 Senzdetta