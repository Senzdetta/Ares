// https://github.com/Senzdetta/Ares

#ifndef module_exec_h
#define module_exec_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

_Static_assert(1, "internal");
#include <console/command_interface.h>
#include <utils/variable.h>
#include <utils/color.h>
#include <utils/missing_argument.h>
#include <utils/setup_shell.h>
#include <utils/genboot.h>

static inline void exec_execute(int argc, char **argv) {
    if (
        argc <= 0 ||
        argv == NULL ||
        argv[0] == NULL ||
        argv[0][0] == '\0'
    ) {
        missingArgument();
        return;
    }

    char rcfile_path[PATH_MAX];
    snprintf(
        rcfile_path, sizeof(rcfile_path),
        "%s/console/shell.sh",
        __aresroot__
    );

    size_t cmd_len = 0;
    for (int i = 0; i < argc; i++) {
        cmd_len += strlen(argv[i]) + 1;
    }

    char *full_cmd = malloc(cmd_len);
    if (!full_cmd) {
        fprintf(
            stderr,
            "%s[!] %sAllocation failed: %s%s%s\n",
            color_R, color_N, color_GG, strerror(errno), color_N
        );
        return;
    }
    full_cmd[0] = '\0';

    for (int i = 0; i < argc; i++) {
        strcat(full_cmd, argv[i]);
        if (i < argc - 1) {
            strcat(full_cmd, " ");
        }
    }

    char *argv_exec[] = {
        "Ares Framework Console",
        "--rcfile",
        rcfile_path,
        "-i",
        "-c",
        full_cmd,
        NULL
    };

    genboot();
    setup_shell();

    execvp("bash", argv_exec);
    fprintf(
        stderr,
        "%s[!] %sExec failed: %s%s%s\n",
        color_R, color_N, color_GG, strerror(errno), color_N
    );
    free(full_cmd);
}

static const Command cmd_exec = {
    .flag = "--exec",
    .execute = exec_execute
};

#endif

// Copyright (c) 2026 Senzdetta