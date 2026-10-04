// https://github.com/Senzdetta/Ares

#ifndef GET_FORMATTED_PATH_H
#define GET_FORMATTED_PATH_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>

static inline void get_formatted_path(
    const char *pwd,
    const char *home,
    int dirtrim,
    char *cpath,
    size_t max_len
) {
    char working_path[2048];
    int is_home = 0;
    size_t home_len = home ?
        strlen(home) :
        0;

    if (
        home &&
        strncmp(
            pwd, home, home_len
        ) == 0 &&
        (
            pwd[home_len] == '/' ||
            pwd[home_len] == '\0'
        )
    ) {
        snprintf(
            working_path,
            sizeof(working_path),
            "~%s",
            pwd + home_len
        );
        is_home = 1;
    } else {
        snprintf(
            working_path,
            sizeof(working_path),
            "%s",
            pwd
        );
    }

    if (dirtrim > 0) {
        int slashes_found = 0;
        int len = strlen(working_path);
        int i = len - 1;

        if (i > 0 && working_path[i] == '/') {
            i--;
        }

        for (; i >= 0; i--) {
            if (working_path[i] == '/') {
                slashes_found++;
                if (slashes_found == dirtrim) {
                    break;
                }
            }
        }

        int prefix_len = is_home ?
            1 :
            0;

        if (i > prefix_len) {
            if (is_home) {
                snprintf(
                    cpath, max_len,
                    "~/...%s",
                    &working_path[i]
                );
            } else {
                snprintf(
                    cpath, max_len,
                    "/...%s",
                    &working_path[i]
                );
            }
        } else {
            strncpy(
                cpath,
                working_path,
                max_len
            );
        }
    } else {
        strncpy(
            cpath,
            working_path,
            max_len
        );
    }
}

#endif

// Copyright (c) 2026 Senzdetta