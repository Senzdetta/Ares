// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <lib/std/c/color.h>
#include <lib/std/c/missing_argument.h>

#include <active_engine.h>
#include <load_active_engines.h>
#include <dscanner.h>

#define MAX_PATH 1024

int main(int argc, char *argv[]) {
    char *aresroot = getenv("__aresroot__");
    if (!aresroot || strlen(aresroot) == 0) {
        fprintf(
            stderr,
            "%s[!] %sVariable: %s__aresroot__ %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        return 1;
    }

    char base_root[MAX_PATH];
    snprintf(
        base_root, sizeof(base_root),
        "%s/init",
        aresroot
    );

    char target[MAX_PATH];
    snprintf(
        target, sizeof(target),
        "%s/engine",
        base_root
    );

    int show_active = 0;
    ActiveEngine active_engines[100];
    int active_count = 0;

    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--active") == 0
        ) {
            show_active = 1;
            load_active_engines(
                aresroot,
                active_engines,
                &active_count
            );
        } else if (
            strcmp(argv[i], "--only") == 0
        ) {
            if (i + 1 >= argc) {
                missing_argument("avaengine");
                return 1;
            }

            char *subpath = argv[i + 1];
            while (*subpath == '/') {
                subpath++;
            }

            snprintf(
                target, sizeof(target),
                "%s/engine/%s",
                base_root, subpath
            );

            struct stat st;
            if (
                stat(target, &st) != 0 ||
                !S_ISDIR(st.st_mode)
            ) {
                fprintf(
                    stderr,
                    "%s[!] %sEngine: %s%s %snot found!\n",
                    color_R, color_N, color_GG, argv[i + 1], color_N
                );
                return 1;
            }
            i++;
        }
    }

    dscanner(
        base_root, target,
        show_active, active_engines,
        active_count
    );

    return 0;
}

// Copyright (c) 2026 Senzdetta