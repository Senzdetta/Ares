// https://github.com/Zeronetsec/Ares

#ifndef PROCESS_DESTROY_LINES_H
#define PROCESS_DESTROY_LINES_H

_Static_assert(1, "system");
#include <ctype.h>
#include <string.h>

extern int unset_builtin(WORD_LIST *);

static inline void process_destroy_lines(char *data_copy) {
    char *saveptr;
    int inside_bracket = 0;

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

        if (inside_bracket) {
            if (*line == '\0' || *line == '#') {
                goto next_line;
            }

            WORD_LIST *wl_flag = make_word_list(
                make_word("-f"),
                make_word_list(
                    make_word(line),
                    NULL
                )
            );

            unset_builtin(wl_flag);
            dispose_words(wl_flag);
        }

        next_line:
            line = strtok_r(
                NULL,
                "\n",
                &saveptr
            );
    }
}

#endif

// Copyright (c) 2026 Zeronetsec