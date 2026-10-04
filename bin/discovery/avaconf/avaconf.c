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
#include <strip_slashes.h>
#include <scandir_execute_conf.h>

visited_dir_t *visited_dirs = NULL;
size_t visited_count = 0;
size_t visited_cap = 0;

int main(int argc, char *argv[]) {
    char *only = NULL;
    bool show_content = false;
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
        } else if (
            strcmp(argv[i], "--show-content") == 0
        ) {
            show_content = true;
        } else {
            invalid_option(argv[i], "avaconf");
            return 1;
        }
    }

    if (!valid) {
        missing_argument("avaconf");
        return 1;
    }

    const char *config_env = getenv("__config__");
    if (!config_env || strlen(config_env) == 0) {
        fprintf(
            stderr,
            "%s[!] %sEnvironment variable: __config__ not found!\n",
            color_R, color_N
        );
        return 1;
    }

    char target_path[PATH_MAX];
    snprintf(
        target_path,
        sizeof(target_path),
        "%s",
        config_env
    );

    char *clean_filter = NULL;
    if (only) {
        clean_filter = strdup(only);
        clean_filter = strip_slashes(clean_filter);
    }

    bool found = scandir_execute_conf(
        target_path,
        clean_filter,
        show_content
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

    return 0;
}

// Copyright (c) 2026 Zeronetsec