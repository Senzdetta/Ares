// https://github.com/Senzdetta/Ares

#ifndef module_uwu_h
#define module_uwu_h

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <console/command_interface.h>
#include <utils/variable.h>
#include <utils/color.h>

static inline void uwu_execute(int argc, char **argv) {
    (void)argc;
    (void)argv;

    const char *faces[] = {
        "(｡◕‿◕｡)",
        "(≧◡≦)",
        "ʕ•ᴥ•ʔ",
        "(・ω・)",
        "(๑˃ᴗ˂)ﻭ",
        "(ง'̀-'́)ง",
        "(=^･ω･^=)"
    };

    size_t faces_count = sizeof(faces) / sizeof(faces[0]);
    const char *fixface = "(・ω・)";

    int delay_ms = 200;
    double duration = 5.0;

    struct timespec start, now;
    clock_gettime(
        CLOCK_MONOTONIC,
        &start
    );
    size_t kaomoji = 0;

    printf("\x1b[?25l");
    fflush(stdout);

    while (1) {
        clock_gettime(
            CLOCK_MONOTONIC,
            &now
        );

        double elapsed = (now.tv_sec - start.tv_sec) +
            (now.tv_nsec - start.tv_nsec) / 1e9;

        if (elapsed >= duration) {
            break;
        }

        printf(
            "\r%s\x1b[K",
            faces[kaomoji % faces_count]
        );
        fflush(stdout);

        struct timespec ts = {
            .tv_sec = delay_ms / 1000,
            .tv_nsec = (delay_ms % 1000) * 1000000L
        };
        nanosleep(&ts, NULL);
        kaomoji++;
    }

    printf(
        "\r%s\x1b[K\x1b[?25h\n",
        fixface
    );
    fflush(stdout);
}

static const Command cmd_uwu = {
    .flag = "--uwu",
    .execute = uwu_execute
};

#endif

// Copyright (c) 2026 Senzdetta