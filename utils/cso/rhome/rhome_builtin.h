// https://github.com/Senzdetta/Ares

#ifndef rhome_builtin_h
#define rhome_builtin_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <trim_whitespace.h>

static inline int rhome_builtin(WORD_LIST *list) {
    char *config_var = get_string_value("__config__");
    char *orig_home = get_string_value("HOME");
    char *new_home = NULL;
    char filepath[1024];

    if (config_var && *config_var) {
        snprintf(
            filepath,
            sizeof(filepath),
            "%s/startup.conf",
            config_var
        );

        FILE *fp = fopen(filepath, "r");
        if (fp) {
            char line[1024];
            while (fgets(line, sizeof(line), fp)) {
                char *trimmed = trim_whitespace(line);
                if (strncmp(trimmed, "home", 4) == 0) {
                    char *p = trimmed + 4;

                    while (*p == ' ' || *p == '\t') p++;
                    if (*p == '=') {
                        p++;
                        while (*p == ' ' || *p == '\t') p++;
                        if (*p != '\0') {
                            new_home = strdup(p);
                        }
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }

    char *final_home = NULL;

    if (new_home) {
        if (
            strcmp(new_home, "~") == 0 || 
            strcmp(new_home, "${HOME}") == 0 || 
            strcmp(new_home, "$HOME") == 0
        ) {
            final_home = orig_home ?
                strdup(orig_home) :
                strdup("/");
        } else if (
            strncmp(new_home, "~/", 2) == 0 &&
            orig_home
        ) {
            final_home = malloc(
                strlen(orig_home) + strlen(new_home)
            );

            sprintf(
                final_home,
                "%s/%s",
                orig_home, new_home + 2
            );
        } else {
            final_home = strdup(new_home);
        }
        free(new_home);
    } else {
        final_home = orig_home ?
            strdup(orig_home) :
            strdup("/");
    }

    SHELL_VAR *v = bind_variable(
        "HOME",
        final_home,
        0
    );

    if (v) {
        VSETATTR(
            v,
            att_exported
        );
    }

    free(final_home);
    return EXECUTION_SUCCESS;
}

#endif

// Copyright (c) 2026 Senzdetta