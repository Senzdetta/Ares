// https://github.com/Zeronetsec/Ares

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

_Static_assert(1, "ares");
#include <color.h>
#include <missing_argument.h>

_Static_assert(1, "internal");
#include <config.h>
#include <contains.h>
#include <build_file_cmd.h>
#include <download_gdrive.h>
#include <clone_git.h>
#include <download_file.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        missing_argument("adl");
        return 1;
    }

    Config cfg = {0};
    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--timeout") == 0 &&
            i + 1 < argc
        ) {
            cfg.timeout = atoi(argv[++i]);
        } else if (
            strcmp(argv[i], "--threads") == 0 &&
            i + 1 < argc
        ) {
            cfg.threads = atoi(argv[++i]);
        } else if (
            strcmp(argv[i], "--out") == 0 &&
            i + 1 < argc
        ) {
            cfg.out = argv[++i];
        } else if (argv[i][0] != '-') {
            cfg.url = argv[i];
        }
    }

    if (!cfg.url) {
        missing_argument("adl");
        return 1;
    }

    if (
        contains(cfg.url, "drive.google.com/file/d/")
    ) {
        download_gdrive(cfg);
    } else if (
        (
            contains(cfg.url, "github.com") ||
            contains(cfg.url, "gitlab.com") ||
            contains(cfg.url, "codeberg.org") ||
            contains(cfg.url, "bitbucket.org") ||
            contains(cfg.url, "sourceforge.net") ||
            contains(cfg.url, "gitea.com") ||
            contains(cfg.url, "sr.ht") ||
            contains(cfg.url, "launchpad.net") ||
            contains(cfg.url, "savannah.gnu.org") ||
            contains(cfg.url, "dev.azure.com") ||
            contains(cfg.url, "gitee.com") ||
            contains(cfg.url, "framagit.org") ||
            contains(cfg.url, "git.disroot.org") ||
            contains(cfg.url, ".git")
        ) &&
        !contains(cfg.url, "raw.githubusercontent.com") &&
        !contains(cfg.url, "/raw/") &&
        !contains(cfg.url, "/releases/download/") &&
        !contains(cfg.url, "/blob/") &&
        !contains(cfg.url, "/downloads/") &&
        !contains(cfg.url, "/get/") &&
        !contains(cfg.url, "/file/")
    ) {
        clone_git(cfg);
    } else {
        download_file(cfg);
    }

    return 0;
}

// Copyright (c) 2026 Zeronetsec