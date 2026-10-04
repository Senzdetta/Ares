// https://github.com/Zeronetsec/Ares

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

_Static_assert(1, "ares");
#include <color.h>
#include <missing_argument.h>
#include <invalid_option.h>

_Static_assert(1, "internal");
#include <visited_dir.h>
#include <strip_slashes.h>
#include <scandir_execute_lib.h>

int main(int argc, char *argv[]) {
    bool allpath = false;
    char *only = NULL;
    bool valid = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--allpath") == 0) {
            allpath = true;
        } else if (strcmp(argv[i], "--only") == 0) {
            if (i + 1 < argc) {
                only = argv[i + 1];
                i++;
            } else {
                valid = false;
                break;
            }
        } else {
            invalid_option(argv[i], "avalib");
            return 1;
        }
    }

    if (!valid) {
        missing_argument("avalib");
        return 1;
    }

    const char *prefix_env = getenv("PREFIX");
    if (!prefix_env || strlen(prefix_env) == 0) {
        prefix_env = "/usr";
    }

    const char *lib_env = getenv("__lib__");
    char default_sys_lib[PATH_MAX];
    snprintf(
        default_sys_lib,
        sizeof(default_sys_lib),
        "%s/lib:/lib:/usr/lib:%s/include:/include:/usr/include",
        prefix_env, prefix_env
    );

    const char *source_env = NULL;

    if (allpath) {
        const char *ld_path = getenv("LD_LIBRARY_PATH");
        if (ld_path && strlen(ld_path) > 0) {
            static char combined[PATH_MAX * 2];
            snprintf(
                combined,
                sizeof(combined),
                "%s:%s",
                default_sys_lib,
                ld_path
            );
            source_env = combined;
        } else {
            source_env = default_sys_lib;
        }
    } else {
        source_env = lib_env;
    }

    if (!source_env || strlen(source_env) == 0) {
        fprintf(
            stderr,
            "%s[!] %sEnvironment variable: __lib__ not found!\n",
            color_R, color_N
        );
        return 1;
    }

    char *clean_filter = NULL;
    if (only) {
        clean_filter = strdup(only);
        clean_filter = strip_slashes(clean_filter);
    }

    bool found_any = false;

    char *source_dup = strdup(source_env);
    char *saveptr;
    char *p = strtok_r(
        source_dup,
        ":",
        &saveptr
    );

    while (p != NULL) {
        if (strlen(p) > 0) {
            if (scandir_execute_lib(p, clean_filter)) {
                found_any = true;
            }
        }
        p = strtok_r(
            NULL,
            ":",
            &saveptr
        );
    }
    free(source_dup);

    if (clean_filter && !found_any) {
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