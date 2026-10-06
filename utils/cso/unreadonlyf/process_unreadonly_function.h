// https://github.com/Senzdetta/Ares

#ifndef process_unreadonly_function_h
#define process_unreadonly_function_h

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