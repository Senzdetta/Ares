// https://github.com/Zeronetsec/Ares

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

_Static_assert(1, "ares");
#include <color.h>
#include <missing_argument.h>
#include <invalid_option.h>

_Static_assert(1, "internal");
#include <visited_dir_t.h>
#include <registered_llsi_t.h>
#include <strip_slashes.h>
#include <init_registered_llsi.h>
#include <free_registered_llsi.h>
#include <parse_llsi_init.h>
#include <scandir_execute_llsi.h>

visited_dir_t *visited_dirs = NULL;
size_t visited_count = 0;
size_t visited_cap = 0;

int main(int argc, char *argv[]) {
    char *only = NULL;
    bool fullscan = false;
    bool valid = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--only") == 0) {
            if (i + 1 < argc) {
                only = argv[i + 1];
                i++;
            } else {
                valid = false;
                break;
            }
        } else if (strcmp(argv[i], "--fullscan") == 0) {
            fullscan = true;
        } else {
            invalid_option(argv[i], "avallsi");
            return 1;
        }
    }

    if (!valid) {
        missing_argument("avallsi");
        return 1;
    }

    const char *aresroot_env = getenv("__aresroot__");
    if (!aresroot_env || strlen(aresroot_env) == 0) {
        fprintf(
            stderr,
            "%s[!] %sEnvironment variable: __aresroot__ not found!\n",
            color_R, color_N
        );
        return 1;
    }

    const char *init_env = getenv("__init__");
    if (!init_env || strlen(init_env) == 0) {
        fprintf(
            stderr,
            "%s[!] %sEnvironment variable: __init__ not found!\n",
            color_R, color_N
        );
        return 1;
    }

    char init_file_path[PATH_MAX];
    snprintf(
        init_file_path,
        sizeof(init_file_path),
        "%s/llsi.init",
        init_env
    );

    registered_llsi_t registered;
    init_registered_llsi(&registered);

    parse_llsi_init(
        init_file_path,
        &registered
    );

    char target_path[PATH_MAX];
    snprintf(
        target_path,
        sizeof(target_path),
        "%s",
        aresroot_env
    );

    char *clean_filter = NULL;
    if (only) {
        clean_filter = strdup(only);
        clean_filter = strip_slashes(clean_filter);
    }

    bool found = scandir_execute_llsi(
        target_path,
        clean_filter,
        fullscan,
        &registered
    );

    if (clean_filter && !found) {
        fprintf(
            stderr,
            "%s[!] %sPath: %s%s %snot found!\n",
            color_R, color_N, color_GG, only, color_N
        );
    }

    if (clean_filter) {
        free(clean_filter);
    }

    if (visited_dirs) {
        free(visited_dirs);
    }

    free_registered_llsi(&registered);

    return 0;
}

// Copyright (c) 2026 Zeronetsec