// https://github.com/Senzdetta/Ares

#ifndef PROCESS_UNREADONLY_VARIABLE_H
#define PROCESS_UNREADONLY_VARIABLE_H

extern void builtin_error(const char *format, ...);

static inline int process_unreadonly_variable(
    const char *var_name
) {
    SHELL_VAR *var = find_variable(var_name);
    if (var) {
        VUNSETATTR(
            var,
            att_readonly
        );
        return EXECUTION_SUCCESS;
    } else {
        builtin_error(
            "%s: variable not found!",
            var_name
        );
        return EXECUTION_FAILURE;
    }
}

#endif

// Copyright (c) 2026 Senzdetta