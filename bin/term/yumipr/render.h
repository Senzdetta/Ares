// https://github.com/Senzdetta/Ares

#ifndef render_h
#define render_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

_Static_assert(1, "ares");
#include <color.h>
#include <read_current_theme.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline void render(void) {
    const char *env_data = getenv("__data__");
    if (!env_data) {
        fprintf(
            stderr,
            "%s[!] %sVariable: %s$__data__ %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        exit(EXIT_FAILURE);
    }

    char theme_rel_path[MAX_PATH];
    if (!read_current_theme(
        theme_rel_path, sizeof(theme_rel_path)
    )) {
        fprintf(
            stderr,
            "%s[!] %sTheme not set!\n",
            color_R, color_N
        );
        exit(EXIT_FAILURE);
    }

    char full_exec_path[MAX_PATH];
    snprintf(
        full_exec_path, sizeof(full_exec_path),
        "%s/yumipr/%s",
        env_data, theme_rel_path
    );

    if (access(full_exec_path, X_OK) != 0) {
        fprintf(
            stderr,
            "%s[!] %sTheme: %s%s %snot found!\n",
            color_R, color_N, color_GG, full_exec_path, color_N
        );
        exit(EXIT_FAILURE);
    }

    char *const argv[] = { full_exec_path, NULL };
    extern char **environ;

    execve(full_exec_path, argv, environ);
    perror("failed to execute theme");
    exit(EXIT_FAILURE);
}

#endif

// Copyright (c) 2026 Senzdetta