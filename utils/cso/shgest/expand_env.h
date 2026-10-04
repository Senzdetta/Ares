// https://github.com/Senzdetta/Ares

#ifndef EXPAND_ENV_H
#define EXPAND_ENV_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static inline char *expand_env(const char *path) {
    if (!path) {
        return NULL;
    }

    if (path[0] == '~') {
        const char *home = getenv("HOME");
        if (!home) {
            return strdup(path);
        }

        size_t home_len = strlen(home);
        size_t rest_len = strlen(path + 1);
        char *expanded = malloc(home_len + rest_len + 1);
        if (expanded) {
            snprintf(
                expanded,
                home_len + rest_len + 1,
                "%s%s",
                home, path + 1
            );
        }

        return expanded;
    }

    if (path[0] == '$') {
        const char *slash = strchr(path, '/');
        size_t var_name_len = slash ?
            (size_t)(slash - (path + 1)) :
            strlen(path + 1);

        if (var_name_len == 0) {
            return strdup(path);
        }

        char var_name[256] = {0};
        if (var_name_len < sizeof(var_name)) {
            strncpy(var_name, path + 1, var_name_len);
            var_name[var_name_len] = '\0';
        }

        const char *val = getenv(var_name);
        if (!val) {
            return strdup(path);
        }

        const char *rest = slash ? slash : "";
        size_t val_len = strlen(val);
        size_t rest_len = strlen(rest);

        char *expanded = malloc(val_len + rest_len + 1);
        if (expanded) {
            snprintf(
                expanded,
                val_len + rest_len + 1,
                "%s%s",
                val, rest
            );
        }
        return expanded;
    }

    return strdup(path);
}

#endif

// Copyright (c) 2026 Senzdetta