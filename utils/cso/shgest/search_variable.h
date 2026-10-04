// https://github.com/Senzdetta/Ares

#ifndef SEARCH_VARIABLE_H
#define SEARCH_VARIABLE_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>

extern SHELL_VAR **all_shell_variables (void);

static inline char *search_variable(
    const char *input,
    size_t len
) {
    const char *last_word = strrchr(input, ' ');
    if (last_word) {
        last_word++;
    } else {
        last_word = input;
    }

    const char *dollar = strrchr(last_word, '$');
    if (!dollar) {
        return NULL;
    }

    const char *var_prefix = dollar + 1;
    size_t var_prefix_len = strlen(var_prefix);

    SHELL_VAR **vars = all_shell_variables();
    if (!vars) {
        return NULL;
    }

    char *res = NULL;
    for (int i = 0; vars[i]; i++) {
        if (
            vars[i]->name &&
            strncmp(
                vars[i]->name,
                var_prefix,
                var_prefix_len
            ) == 0
        ) {
            if (strlen(vars[i]->name) > var_prefix_len) {
                size_t prefix_len = dollar - input + 1;
                size_t full_len = prefix_len + strlen(
                    vars[i]->name
                ) + 1;

                res = malloc(full_len);
                if (res) {
                    strncpy(
                        res,
                        input,
                        prefix_len
                    );
                    res[prefix_len] = '\0';
                    strcat(
                        res,
                        vars[i]->name
                    );
                }
                break;
            }
        }
    }
    free(vars);
    return res;
}

#endif

// Copyright (c) 2026 Senzdetta