// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <string.h>

#include <lib/std/c/missing_argument.h>
#include <lib/std/c/invalid_option.h>

#include <get_target_path.h>
#include <handle_ls.h>
#include <handle_scandup.h>
#include <handle_ctgroup.h>
#include <handle_ctmod.h>
#include <handle_rngroup.h>
#include <handle_rnmod.h>
#include <handle_toggle.h>

int main(int argc, char *argv[]) {
    char filepath[512];
    get_target_path(
        filepath, sizeof(filepath)
    );

    if (argc < 2) {
        missing_argument("lpatch");
        return 1;
    }

    if (strcmp(argv[1], "--dupscan") == 0) {
        return handle_scandup(
            filepath
        );
    }

    if (strcmp(argv[1], "--lsgroup") == 0) {
        int show_mod = 0;
        if (
            argc > 2 &&
            strcmp(argv[2], "--lsmod") == 0
        ) {
            show_mod = 1;
        }

        handle_ls(
            filepath, show_mod
        );

        return 0;
    }

    if (strcmp(argv[1], "--ctgroup") == 0) {
        if (argc < 3) {
            missing_argument("lpatch");
            return 1;
        }

        return handle_ctgroup(
            filepath, argv[2]
        );
    }

    if (strcmp(argv[1], "--ctmod") == 0) {
        if (
            argc < 6 ||
            strcmp(argv[4], "--group") != 0
        ) {
            missing_argument("lpatch");
            return 1;
        }

        return handle_ctmod(
            filepath,
            argv[2], argv[3], argv[5]
        );
    }

    if (strcmp(argv[1], "--rngroup") == 0) {
        if (argc < 4) {
            missing_argument("lpatch");
            return 1;
        }

        return handle_rngroup(
            filepath, argv[2], argv[3]
        );
    }

    if (strcmp(argv[1], "--rnmod") == 0) {
        if (argc < 4) {
            missing_argument("lpatch");
            return 1;
        }

        const char *new_dest = NULL;
        for (int i = 4; i < argc; i++) {
            if (
                strcmp(argv[i], "--llsi") == 0 &&
                i + 1 < argc
            ) {
                new_dest = argv[i + 1];
                break;
            }
        }

        return handle_rnmod(
            filepath, argv[2], argv[3], new_dest
        );
    }

    int enable;
    if (strcmp(argv[1], "--enable") == 0) {
        enable = 1;
    } else if (strcmp(argv[1], "--disable") == 0) {
        enable = 0;
    } else {
        invalid_option(argv[1], "lpatch");
        return 1;
    }

    if (argc < 3) {
        missing_argument("lpatch");
        return 1;
    }

    const char *mod = NULL;
    for (int i = 3; i < argc; i++) {
        if (
            strcmp(argv[i], "--mod") == 0 &&
            i + 1 < argc
        ) {
            mod = argv[i + 1];
            break;
        }
    }

    return handle_toggle(
        filepath, enable, argv[2], mod
    );
}

// Copyright (c) 2026 Senzdetta