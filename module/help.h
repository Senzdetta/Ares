// https://github.com/Senzdetta/Ares

#ifndef module_help_h
#define module_help_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <console/command_interface.h>
#include <utils/variable.h>
#include <utils/color.h>
#include <utils/banner.h>
#include <utils/birthday.h>

static inline void help_execute(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char engine_path[PATH_MAX];
    snprintf(
        engine_path, sizeof(engine_path),
        "%s/utils/go/json_parser",
        __aresroot__
    );

    if (access(engine_path, F_OK) == 0) {
        banner();
        birthday();

        printf(
            "%sUsage: %sares %s<option> [<args>]%s\n\n",
            color_N, color_GG, color_CC, color_N
        );

        printf(
            "%sAvailable options:\n",
            color_N
        );

        if (access(engine_path, X_OK) != 0) {
            chmod(
                engine_path,
                S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH
            );
        }

        int status = system(engine_path);
        (void)status;
    } else {
        printf(
            "%s[!] %sEngine: %s%s %snot found!\n",
            color_R, color_N, color_GG, engine_path, color_N
        );
    }
}

static const Command cmd_help = {
    .flag = "--help",
    .execute = help_execute
};

#endif

// Copyright (c) 2026 Senzdetta