// https://github.com/Senzdetta/Ares

#ifndef UNREADONLYV_BUILTIN_H
#define UNREADONLYV_BUILTIN_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <builtins.h>

_Static_assert(1, "internal");
#include <validate_input.h>
#include <trim_line.h>
#include <process_unreadonly_variable.h>

static inline int unreadonlyv_builtin(WORD_LIST *list) {
    char *input_data = validate_input(list);
    if (!input_data) {
        return EXECUTION_FAILURE;
    }

    char *data_copy = strdup(input_data);
    if (!data_copy) {
        return EXECUTION_FAILURE;
    }

    char *saveptr;
    int inside_bracket = 0;
    int final_status = EXECUTION_SUCCESS;

    char *line = strtok_r(
        data_copy,
        "\n",
        &saveptr
    );

    while (line != NULL) {
        line = trim_line(line);

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
            if (
                process_unreadonly_variable(
                    line
                ) != EXECUTION_SUCCESS
            ) {
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

    free(data_copy);
    return final_status;
}

#endif

// Copyright (c) 2026 Senzdetta