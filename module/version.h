// https://github.com/Senzdetta/Ares

#ifndef module_version_h
#define module_version_h

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "internal");
#include <console/command_interface.h>
#include <utils/color.h>

static inline void version_execute(int argc, char **argv) {
    (void)argc;
    (void)argv;

    const char *name = "Ares";
    const char *version = "v0.1.20261007";
    const char *developer = "Senzdetta";
    const char *homepage = "https://github.com/Senzdetta/Ares";

    printf(
        "%s- %s%s %s-%s\n",
        color_DG, color_GG, name, color_DG, color_N
    );

    printf(
        "%sVersion: %s%s%s\n",
        color_N, color_GG, version, color_N
    );

    printf(
        "%sDeveloper: %s%s%s\n",
        color_N, color_GG, developer, color_N
    );

    printf(
        "%sHomepage: %s%s%s\n",
        color_N, color_GG, homepage, color_N
    );
}

static const Command cmd_version = {
    .flag = "--version",
    .execute = version_execute
};

#endif

// Copyright (c) 2026 Senzdetta