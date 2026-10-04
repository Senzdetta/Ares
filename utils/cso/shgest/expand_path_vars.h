// https://github.com/Senzdetta/Ares

#ifndef EXPAND_PATH_VARS_H
#define EXPAND_PATH_VARS_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SHELL_VAR **all_shell_variables (void);

static inline void expand_path_vars(
    const char *src,
    char *dest,
    size_t dest_size
) {
    if (src[0] == '$') {
        const char *slash = strchr(src, '/');
        size_t var_name_len = slash ?
            (size_t)(slash - (src + 1)) :
            strlen(src + 1);

        char var_name[256];
        if (var_name_len < sizeof(var_name)) {
            strncpy(
                var_name,
                src + 1,
                var_name_len
            );
            var_name[var_name_len] = '\0';

            SHELL_VAR **vars = all_shell_variables();
            if (vars) {
                for (int i = 0; vars[i]; i++) {
                    if (
                        vars[i]->name &&
                        strcmp(vars[i]->name, var_name) == 0
                    ) {
                        char *val = get_variable_value(vars[i]);
                        if (val) {
                            snprintf(
                                dest,
                                dest_size,
                                "%s%s",
                                val, slash ? slash : ""
                            );
                            free(vars);
                            return;
                        }
                    }
                }
                free(vars);
            }
        }
    }
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

#endif

// Copyright (c) 2026 Senzdetta