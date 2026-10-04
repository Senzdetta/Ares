// https://github.com/Senzdetta/Ares

#ifndef module_chstartup_h
#define module_chstartup_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "internal");
#include <console/command_interface.h>
#include <utils/variable.h>
#include <utils/color.h>

static inline void chstartup_execute(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char engine[PATH_MAX];
    char config[PATH_MAX];

    snprintf(
        engine, sizeof(engine),
        "%s/bin/core/chstartup",
        __aresroot__
    );

    snprintf(
        config, sizeof(config),
        "%s/config",
        __aresroot__
    );

    if (access(engine, F_OK) == 0) {
        if (access(engine, X_OK) != 0) {
            chmod(
                engine,
                S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH
            );
        }

        setenv("__config__", config, 1);
        int status = system(engine);
        (void)status;
        unsetenv("__config__");
    } else {
        printf(
            "%s[!] %sEngine: %s%s %snot found!\n",
            color_R, color_N, color_GG, engine, color_N
        );
    }
}

static const Command cmd_chstartup = {
    .flag = "--chstartup",
    .execute = chstartup_execute
};

#endif

// Copyright (c) 2026 Senzdetta