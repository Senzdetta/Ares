// https://github.com/Senzdetta/Ares

#ifndef utils_setup_shell_h
#define utils_setup_shell_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

_Static_assert(1, "internal");
#include <utils/variable.h>

static inline void setup_shell(void) {
    const char *prefix = getenv("PREFIX");
    if (prefix == NULL || prefix[0] == '\0') {
        prefix = "/usr";
    }
    setenv("PREFIX", prefix, 1);

    const char *home = getenv("HOME");

    char aresrc[PATH_MAX];
    char areslog[PATH_MAX];
    char shmoduser[PATH_MAX];

    snprintf(
        aresrc, sizeof(aresrc),
        "%s/.aresrc",
        home
    );

    snprintf(
        areslog, sizeof(areslog),
        "%s/.ares_log",
        home
    );

    snprintf(
        shmoduser, sizeof(shmoduser),
        "%s/.ares/init/shmod",
        home
    );

    setenv("__aresroot__", __aresroot__, 1);
    setenv("__aresrc__", aresrc, 1);
    setenv("__areslog__", areslog, 1);
    setenv("__shmoduser__", shmoduser, 1);

    char progname[PATH_MAX];
    ssize_t n = readlink(
        "/proc/self/exe", progname, sizeof(progname) - 1
    );

    if (n > 0) {
        progname[n] = '\0';
    } else {
        strcpy(progname, "ares");
    }

    setenv("SHELL", progname, 1);
}

#endif

// Copyright (c) 2026 Senzdetta