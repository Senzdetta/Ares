// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unescape_string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    const char *raw_delimiter = "";

    int str_start_idx = -1;
    int use_stdin = 0;

    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--del") == 0 &&
            (i + 1) < argc
        ) {
            raw_delimiter = argv[++i];
        } else if (
            strcmp(argv[i], "--stdin") == 0
        ) {
            use_stdin = 1;
        } else if (
            strcmp(argv[i], "--str") == 0
        ) {
            str_start_idx = i + 1;
            break;
        }
    }

    char *delimiter = unescape_string(raw_delimiter);
    if (!delimiter) {
        delimiter = strdup("");
    }

    if (use_stdin) {
        char line[1024];
        int first = 1;

        while (fgets(line, sizeof(line), stdin) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            if (!first) {
                printf("%s", delimiter);
            }
            printf("%s", line);
            first = 0;
        }
        printf("\n");
    } else if (
        str_start_idx != -1 &&
        str_start_idx < argc
    ) {
        for (int i = str_start_idx; i < argc; i++) {
            printf("%s", argv[i]);
            if (i < argc - 1) {
                printf("%s", delimiter);
            }
        }
        printf("\n");
    }

    free(delimiter);
    return 0;
}

// Copyright (c) 2026 Senzdetta