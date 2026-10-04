// https://github.com/Senzdetta/Ares

#ifndef PROCESS_UNREADONLY_FUNCTION_H
#define PROCESS_UNREADONLY_FUNCTION_H

extern void builtin_error(const char *format, ...);

static inline int process_unreadonly_function(const char *func_name) {
    SHELL_VAR *func = find_function(func_name);
    if (func) {
        VUNSETATTR(
            func,
            att_readonly
        );
        return EXECUTION_SUCCESS;
    } else {
        builtin_error(
            "%s: function not found!",
            func_name
        );
        return EXECUTION_FAILURE;
    }
}

#endif

// Copyright (c) 2026 Senzdetta