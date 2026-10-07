// https://github.com/Senzdetta/Ares

#ifndef module_shell_h
#define module_shell_h

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <console/command_interface.h>
#include <utils/variable.h>
#include <utils/color.h>
#include <utils/setup_shell.h>
#include <utils/genboot.h>

static inline void shell_execute(int argc, char **argv) {
    (void)argc; 
    (void)argv;

    char rcfile_path[PATH_MAX];
    snprintf(
        rcfile_path, sizeof(rcfile_path),
        "%s/console/shell.sh",
        __aresroot__
    );

    char *argv_exec[] = {
        "Ares Framework Console",
        "--rcfile",
        rcfile_path,
        "-i",
        NULL
    };

    genboot();
    setup_shell();

    execvp("bash", argv_exec);
    fprintf(
        stderr,
        "%s[!] %sExec shell error: %s%s%s\n",
        color_R, color_N, color_GG, strerror(errno), color_N
    );
}

static const Command cmd_shell = {
    .flag = "--shell",
    .execute = shell_execute
};

#endif

// Copyright (c) 2026 Senzdetta