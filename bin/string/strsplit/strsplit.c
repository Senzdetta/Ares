// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <read_stdin.h>
#include <process_split.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    const char *delimiter = " ";
    const char *input_str = NULL;
    const char *range_expr = "0";

    int use_stdin = 0;

    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--del") == 0 &&
            (i + 1) < argc
        ) {
            delimiter = argv[++i];
        } else if (
            strcmp(argv[i], "--index") == 0 &&
            (i + 1) < argc
        ) {
            range_expr = argv[++i];
        } else if (
            strcmp(argv[i], "--str") == 0 &&
            (i + 1) < argc
        ) {
            input_str = argv[++i];
        } else if (
            strcmp(argv[i], "--stdin") == 0
        ) {
            use_stdin = 1;
        }
    }

    if (use_stdin) {
        char *stdin_data = read_stdin();
        process_split(
            stdin_data, delimiter, range_expr
        );

        if (stdin_data) {
            free(stdin_data);
        }
    } else {
        process_split(
            input_str, delimiter, range_expr
        );
    }

    return 0;
}

// Copyright (c) 2026 Senzdetta