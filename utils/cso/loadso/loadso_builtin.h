// https://github.com/Senzdetta/Ares

#ifndef LOADSO_BUILTIN_H
#define LOADSO_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

_Static_assert(1, "internal");
#include <enable_single_so.h>

static inline int loadso_builtin(WORD_LIST *list) {
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

    SHELL_VAR *root_var = find_variable("__aresroot__");
    char *root = root_var ?
        value_cell(root_var) :
        ".";

    char *data_copy = strdup(input_data);
    if (!data_copy) {
        return EXECUTION_FAILURE;
    }

    char *saveptr;
    int inside_bracket = 0;
    int status = EXECUTION_SUCCESS;

    char *line = strtok_r(
        data_copy,
        "\n",
        &saveptr
    );

    while (line != NULL) {
        while (isspace((unsigned char)*line)) line++;
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

        if (inside_bracket) {
            if (
                *line == '\0' ||
                *line == '#'
            ) {
                goto next_line;
            }

            if (enable_single_so(
                root, line
            ) != EXECUTION_SUCCESS) {
                status = EXECUTION_FAILURE;
                break;
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
    return status;
}

#endif

// Copyright (c) 2026 Senzdetta