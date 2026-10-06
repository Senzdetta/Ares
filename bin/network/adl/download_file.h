// https://github.com/Senzdetta/Ares

#ifndef download_file_h
#define download_file_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <config.h>
#include <build_file_cmd.h>

static inline void download_file(Config cfg) {
    char final_url[512];
    if (strncmp(cfg.url, "http", 4) != 0) {
        snprintf(
            final_url,
            sizeof(final_url),
            "https://%s",
            cfg.url
        );
    } else {
        snprintf(
            final_url,
            sizeof(final_url),
            "%s",
            cfg.url
        );
    }

    char cmd[1024] = {0};
    build_file_cmd(
        cmd,
        sizeof(cmd),
        cfg,
        final_url
    );

    printf(
        "%s[+] %sExecuting: %s%s%s\n",
        color_B, color_N, color_GG, cmd, color_N
    );

    system(cmd);
}

#endif

// Copyright (c) 2026 Senzdetta