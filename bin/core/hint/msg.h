// https://github.com/Senzdetta/Ares

#ifndef MSG_H
#define MSG_H

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "ares");
#include <color.h>

static inline void msg() {
    printf(
        "%sUsage:\n"
        "    %s- %satoolkit %sto discover all ares binaries.%s\n"
        "    %s- %savadoc %sto display available documentation.%s\n"
        "    %s- %saresdoc %s<name> %sto view specific documentation.%s\n"
        "    %s- %schstartup %sor %sopenfile %sstartup.conf %sto open the tui editor to modify startup configuration.%s\n"
        "    %s- %sreloadshell %sto reload the shell.%s\n"
        "    %s- %senvdump %sto show all alias, function, shortcut, variable, and more.%s\n"
        "    %s- %shelp %sor %shint %sto display this message.%s\n"
        "%s\n",
        color_N,
        color_R, color_GG, color_WW, color_N,
        color_R, color_GG, color_WW, color_N,
        color_R, color_GG, color_CC, color_WW, color_N,
        color_R, color_GG, color_WW, color_GG, color_CC, color_WW, color_N,
        color_R, color_GG, color_WW, color_N,
        color_R, color_GG, color_WW, color_N,
        color_R, color_GG, color_WW, color_GG, color_WW, color_N,
        color_N
    );
}

#endif

// Copyright (c) 2026 Senzdetta