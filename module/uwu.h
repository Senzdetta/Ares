// https://github.com/Senzdetta/Ares

#ifndef module_uwu_h
#define module_uwu_h

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

static inline void uwu_execute(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char engine_path[PATH_MAX];
    snprintf(
        engine_path, sizeof(engine_path),
        "%s/utils/go/nyanners",
        __aresroot__
    );

    if (access(engine_path, F_OK) == 0) {
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

static const Command cmd_uwu = {
    .flag = "--uwu",
    .execute = uwu_execute
};

#endif

// Copyright (c) 2026 Senzdetta