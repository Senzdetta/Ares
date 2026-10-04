// https://github.com/Zeronetsec/Ares

#ifndef DOWNLOAD_GDRIVE_H
#define DOWNLOAD_GDRIVE_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <config.h>
#include <build_file_cmd.h>

static inline void download_gdrive(Config cfg) {
    char *id_start = strstr(cfg.url, "/d/");
    if (!id_start) {
        printf(
            "%s[!] %sInvalid google drive url!\n",
            color_R, color_N
        );
        return;
    }

    id_start += 3;

    char id[128] = {0};
    int i = 0;
    while (
        id_start[i] != '\0' &&
        id_start[i] != '/' &&
        id_start[i] != '?' &&
        i < 127
    ) {
        id[i] = id_start[i];
        i++;
    }

    char final_url[512];
    snprintf(
        final_url,
        sizeof(final_url),
        "https://drive.google.com/uc?export=download&id=%s",
        id
    );

    char cmd[1024] = {0};
    build_file_cmd(
        cmd,
        sizeof(cmd),
        cfg,
        final_url
    );

    printf(
        "%s[*] %sExecuting: %s%s%s\n",
        color_B, color_N, color_GG, cmd, color_N
    );

    system(cmd);
}

#endif

// Copyright (c) 2026 Zeronetsec