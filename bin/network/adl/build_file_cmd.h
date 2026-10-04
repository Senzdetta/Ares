// https://github.com/Senzdetta/Ares

#ifndef BUILD_FILE_CMD_H
#define BUILD_FILE_CMD_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>

_Static_assert(1, "internal");
#include <config.h>

static inline void build_file_cmd(
    char *cmd,
    size_t size, 
    Config cfg,
    const char *target_url
) {
    int pos = 0;
    if (cfg.threads > 1) {
        pos += snprintf(
            cmd + pos,
            size - pos,
            "aria2c -x %d -s %d ",
            cfg.threads, cfg.threads
        );

        if (cfg.out) {
            pos += snprintf(
                cmd + pos,
                size - pos,
                "-d . -o \"%s\" ",
                cfg.out
            );
        } else {
            pos += snprintf(
                cmd + pos,
                size - pos,
                "--content-disposition "
            );
        }

        pos += snprintf(
            cmd + pos,
            size - pos,
            "\"%s\"",
            target_url
        );

        if (cfg.timeout > 0) {
            char temp_cmd[1024];
            snprintf(
                temp_cmd,
                sizeof(temp_cmd),
                "timeout %d %s",
                cfg.timeout, cmd
            );
            strncpy(cmd, temp_cmd, size);
        }
    } else {
        pos += snprintf(
            cmd + pos,
            size - pos,
            "curl -L "
        );

        if (cfg.timeout > 0) {
            pos += snprintf(
                cmd + pos,
                size - pos,
                "--max-time %d ",
                cfg.timeout
            );
        }

        if (cfg.out) {
            pos += snprintf(
                cmd + pos,
                size - pos,
                "-o \"%s\" ",
                cfg.out
            );
        } else {
            pos += snprintf(
                cmd + pos,
                size - pos,
                "-J -O "
            );
        }
        pos += snprintf(
            cmd + pos,
            size - pos,
            "\"%s\"",
            target_url
        );
    }
}

#endif

// Copyright (c) 2026 Senzdetta