// https://github.com/Senzdetta/Ares

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
#include <registered_engine_t.h>
#include <init_registered_engine.h>
#include <free_registered_engine.h>
#include <parse_startup_conf.h>
#include <strip_slashes.h>
#include <scandir_execute_engine.h>

visited_dir_t *visited_dirs = NULL;
size_t visited_count = 0;
size_t visited_cap = 0;

int main(int argc, char *argv[]) {
    char *only = NULL;
    bool active_only = false;
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
        } else if (strcmp(argv[i], "--active") == 0) {
            active_only = true;
        } else {
            invalid_option(argv[i], "avaengine");
            return 1;
        }
    }

    if (!valid) {
        missing_argument("avaengine");
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

    registered_engine_t active_engines;
    init_registered_engine(&active_engines);

    if (active_only) {
        char conf_file_path[PATH_MAX];
        snprintf(
            conf_file_path,
            sizeof(conf_file_path),
            "%s/config/startup.conf",
            aresroot_env
        );

        parse_startup_conf(conf_file_path, &active_engines);
    }

    char target_path[PATH_MAX];
    snprintf(
        target_path,
        sizeof(target_path),
        "%s/init/engine",
        aresroot_env
    );

    char *clean_filter = NULL;
    if (only) {
        clean_filter = strdup(only);
        clean_filter = strip_slashes(clean_filter);
    }

    bool found = scandir_execute_engine(
        target_path,
        clean_filter,
        active_only,
        &active_engines
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

    free_registered_engine(&active_engines);

    return 0;
}

// Copyright (c) 2026 Senzdetta