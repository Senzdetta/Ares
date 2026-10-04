// https://github.com/Zeronetsec/Ares

#ifndef ERROR_BUILTIN_H
#define ERROR_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <format_signal_string.h>

extern int last_command_exit_value;

static inline int error_builtin(WORD_LIST *list) {
    char *cmd = get_string_value("BASH_COMMAND");
    if (!cmd) {
        cmd = "null";
    }

    char *lineno = get_string_value("LINENO");
    if (!lineno) {
        lineno = "0";
    }

    pid_t pid = getpid();
    uid_t euid = geteuid();

    int exit_code = last_command_exit_value;

    char sig_str[64];
    format_signal_string(
        exit_code,
        sig_str,
        sizeof(sig_str)
    );

    size_t mem_len = strlen(cmd) + 1;
    size_t heap_buff = malloc_usable_size((void*)cmd);

    printf(
        "%sAres Framework Console: %serror%s\n",
        color_N, color_R, color_N
    );

    printf(
        "%sAres Framework Console: %ssysexec(%s%s%s)%s::%slineno(%s%s%s)%s::%sproc(%s%d%s)%s::%seuid(%s%d%s)%s::%serror(%s%d%s)%s::%smem(%s%zu%s)%s::%sbuff(%s%zu%s)%s::%saddr(%s%p%s)%s::%sptr(%s%p%s)%s::%ssig(%s) %s-> %s",
        color_N,
        color_WW, color_GG, cmd, color_WW, color_DG,
        color_WW, color_GG, lineno, color_WW, color_DG,
        color_WW, color_YY, pid, color_WW, color_DG,
        color_WW, color_YY, euid, color_WW, color_DG,
        color_WW, color_R, exit_code, color_WW, color_DG,
        color_WW, color_CC, mem_len, color_WW, color_DG,
        color_WW, color_CC, heap_buff, color_WW, color_DG,
        color_WW, color_BB, (void*)&cmd, color_WW, color_DG,
        color_WW, color_BB, (void*)cmd, color_WW, color_DG,
        color_WW, sig_str, color_DG, color_N
    );

    for (size_t i = 0; i < mem_len - 1; i++) {
        printf(
            "%s\\x%02x%s",
            color_GG,
            (unsigned char)cmd[i],
            color_N
        );
    }
    printf("\n");
    return EXECUTION_FAILURE;
}

#endif

// Copyright (c) 2026 Zeronetsec