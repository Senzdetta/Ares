// https://github.com/Senzdetta/Ares

#ifndef process_split_h
#define process_split_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unescape_string.h>

static inline void process_split(
    const char *input_str,
    const char *raw_delimiter,
    const char *range_expr
) {
    if (!input_str) {
        return;
    }

    char *raw_del_unescaped = unescape_string(raw_delimiter);
    const char *delimiter = raw_del_unescaped ?
        raw_del_unescaped :
        " ";

    char *str_copy = strdup(input_str);
    if (!str_copy) {
        if (raw_del_unescaped) {
            free(raw_del_unescaped);
        }
        return;
    }

    char *tokens[2048];
    int count = 0;

    char *token = strtok(str_copy, delimiter);
    while (token != NULL && count < 2048) {
        tokens[count++] = token;
        token = strtok(NULL, delimiter);
    }

    if (count == 0) {
        free(str_copy);
        if (raw_del_unescaped) {
            free(raw_del_unescaped);
        }
        return;
    }

    int start_idx = 0;
    int end_idx = count - 1;

    char *dash = strchr(range_expr, '-');
    if (
        dash &&
        dash != range_expr &&
        *(dash - 1) == '\\'
    ) {
        dash = NULL;
    }

    if (dash && dash != range_expr) {
        char expr[64];
        strncpy(
            expr, range_expr,
            sizeof(expr) - 1
        );
        expr[sizeof(expr) - 1] = '\0';

        char *split_point = strchr(expr + 1, '-'); 
        if (split_point) {
            *split_point = '\0';

            char *p1 = expr;
            char *p2 = split_point + 1;

            if (strlen(p1) > 0) {
                start_idx = atoi(p1);
            }

            if (strlen(p2) > 0) {
                end_idx = atoi(p2);
            } else {
                end_idx = count - 1;
            }
        }
    } else {
        if (dash && *(dash + 1) == '\0') {
            int val = atoi(range_expr);
            start_idx = count + val;
            end_idx = count - 1;
        } else {
            int val = atoi(range_expr);
            if (val < 0) {
                start_idx = count + val;
            } else {
                start_idx = val;
            }
            end_idx = start_idx;
        }
    }

    if (start_idx < 0) {
        start_idx = count + start_idx;
    }

    if (end_idx < 0) {
        end_idx = count + end_idx;
    }

    if (start_idx < 0) {
        start_idx = 0;
    }

    if (end_idx >= count) {
        end_idx = count - 1;
    }

    for (int i = start_idx; i <= end_idx; i++) {
        if (i >= 0 && i < count) {
            printf("%s", tokens[i]);
            if (i < end_idx) {
                printf("%s", delimiter);
            }
        }
    }
    printf("\n");

    free(str_copy);
    if (raw_del_unescaped) {
        free(raw_del_unescaped);
    }
}

#endif

// Copyright (c) 2026 Senzdetta