// https://github.com/Senzdetta/Ares

#ifndef FORMAT_SIGNAL_STRING_H
#define FORMAT_SIGNAL_STRING_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <signal.h>

_Static_assert(1, "ares");
#include <color.h>

static inline void format_signal_string(
    int exit_code,
    char *dest,
    size_t dest_size
) {
    int sig_num = (
        exit_code > 128 &&
        exit_code <= 128 + 64
    ) ?
        (exit_code - 128) :
        0;

    if (sig_num > 0) {
        snprintf(
            dest,
            dest_size,
            "%s%d%s:%s%s%s",
            color_R, sig_num, color_DG,
            color_GG, strsignal(sig_num), color_N
        );
    } else {
        snprintf(
            dest,
            dest_size,
            "%s0%s:%snone%s",
            color_R, color_DG, color_GG, color_N
        );
    }
}

#endif

// Copyright (c) 2026 Senzdetta