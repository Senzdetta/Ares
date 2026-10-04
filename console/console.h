// https://github.com/Zeronetsec/Ares

#ifndef console_console_h
#define console_console_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <console/command_interface.h>
#include <console/pubmod.h>
#include <console/command.h>
#include <utils/missing_argument.h>
#include <utils/invalid_option.h>

static inline void console(int argc, char **argv) {
    if (argc < 2) {
        missingArgument();
        exit(1);
    }

    const char *trigger = argv[1];
    int remaining_argc = argc - 2;
    char **remaining_argv = &argv[2];

    for (int i = 0; commands[i] != NULL; i++) {
        if (strcmp(trigger, commands[i]->flag) == 0) {
            commands[i]->execute(
                remaining_argc, remaining_argv
            );
            return;
        }
    }

    invalidOption(trigger);
    exit(1);
}

#endif

// Copyright (c) 2026 Zeronetsec