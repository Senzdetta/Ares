// https://github.com/Senzdetta/Ares

#ifndef PROCESS_DESTROY_LINES_H
#define PROCESS_DESTROY_LINES_H

_Static_assert(1, "system");
#include <ctype.h>
#include <string.h>

extern int enable_builtin(WORD_LIST *list);

static inline int process_destroy_lines(char *data_copy) {
    char *saveptr;
    int inside_bracket = 0;
    int final_status = EXECUTION_SUCCESS;

    char *line = strtok_r(
        data_copy,
        "\n",
        &saveptr
    );

    while (line != NULL) {
        while (isspace((unsigned char)*line)) {
            line++;
        }

        char *end = line + strlen(line) - 1;
        while (
            end >= line &&
            isspace((unsigned char)*end)
        ) {
            *end = '\0';
            end--;
        }

        if (strchr(line, '(') != NULL) {
            inside_bracket = 1;
            goto next_line;
        }

        if (strchr(line, ')') != NULL) {
            inside_bracket = 0;
            goto next_line;
        }

        if (
            inside_bracket &&
            *line != '\0' &&
            *line != '#'
        ) {
            char *builtin_name = line;

            WORD_LIST *arg_name = make_word_list(
                make_word(builtin_name),
                NULL
            );

            WORD_LIST *enable_args = make_word_list(
                make_word("-d"),
                arg_name
            );

            int enable_status = enable_builtin(enable_args);

            dispose_words(enable_args);
            if (enable_status != EXECUTION_SUCCESS) {
                final_status = EXECUTION_FAILURE;
            }
        }

        next_line:
            line = strtok_r(
                NULL,
                "\n",
                &saveptr
            );
    }

    return final_status;
}

#endif

// Copyright (c) 2026 Senzdetta