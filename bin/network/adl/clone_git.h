// https://github.com/Zeronetsec/Ares

#ifndef CLONE_GIT_H
#define CLONE_GIT_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <config.h>

static inline void clone_git(Config cfg) {
    char cmd[1024] = {0};
    int pos = 0;

    if (cfg.timeout > 0) {
        pos += snprintf(
            cmd + pos,
            sizeof(cmd) - pos,
            "timeout %d ",
            cfg.timeout
        );
    }

    pos += snprintf(
        cmd + pos,
        sizeof(cmd) - pos,
        "git clone "
    );

    if (cfg.threads > 0) {
        pos += snprintf(
            cmd + pos,
            sizeof(cmd) - pos,
            "--jobs %d ",
            cfg.threads
        );
    }

    if (strncmp(cfg.url, "http", 4) != 0) {
        pos += snprintf(
            cmd + pos,
            sizeof(cmd) - pos,
            "\"https://%s\"",
            cfg.url
        );
    } else {
        pos += snprintf(
            cmd + pos,
            sizeof(cmd) - pos,
            "\"%s\"",
            cfg.url
        );
    }

    if (cfg.out) {
        pos += snprintf(
            cmd + pos,
            sizeof(cmd) - pos,
            " \"%s\"",
            cfg.out
        );
    }

    printf(
        "%s[*] %sExecuting: %s%s%s\n",
        color_B, color_N, color_GG, cmd, color_N
    );

    system(cmd);
}

#endif

// Copyright (c) 2026 Zeronetsec