// https://github.com/Zeronetsec/Ares

#ifndef DYNAP_BUILTIN_H
#define DYNAP_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <exclude_list.h>
#include <string_buffer.h>
#include <trim_whitespace.h>
#include <load_exclusions.h>
#include <append_path_list.h>
#include <expand_vars.h>
#include <traverse_and_find_dirs.h>

static inline int dynap_builtin(WORD_LIST *list) {
    StringBuffer new_path = {NULL, 0, 0};
    ExcludeList excludes = {NULL, 0, 0};
    int is_readonly = 0;

    char *config_val = get_string_value("__config__");
    char *aresroot = get_string_value("__aresroot__");

    if (config_val && *config_val) {
        load_exclusions(
            config_val, &excludes
        );
    } else if (aresroot && *aresroot) {
        char fallback_cfg[PATH_MAX];
        snprintf(
            fallback_cfg,
            sizeof(fallback_cfg),
            "%s/config",
            aresroot
        );

        load_exclusions(
            fallback_cfg, &excludes
        );
    }

    if (aresroot && *aresroot) {
        char config_file[PATH_MAX];
        snprintf(
            config_file,
            sizeof(config_file),
            "%s/config/startup.conf",
            aresroot
        );

        FILE *fp = fopen(config_file, "r");
        if (fp) {
            char line[4096];
            while (fgets(line, sizeof(line), fp)) {
                char *trimmed = trim_whitespace(line);
                if (strncmp(trimmed, "toolkit", 7) == 0) {
                    char *eq = strchr(trimmed, '=');
                    if (eq) {
                        char *val = eq + 1;

                        char *ro_pos = strstr(
                            val,
                            "<+readonly>"
                        );

                        if (ro_pos) {
                            is_readonly = 1;
                            *ro_pos = '\0';
                        } else {
                            char *nro_pos = strstr(
                                val,
                                "<-readonly>"
                            );

                            if (nro_pos) {
                                is_readonly = 0;
                                *nro_pos = '\0';
                            }
                        }

                        char *token = strtok(val, ",");
                        while (token) {
                            char *clean_tok = trim_whitespace(token);
                            if (*clean_tok) {
                                char expanded[PATH_MAX];
                                expand_vars(
                                    clean_tok,
                                    expanded,
                                    sizeof(expanded)
                                );

                                if (*expanded) {
                                    traverse_and_find_dirs(
                                        expanded,
                                        &new_path,
                                        &excludes
                                    );
                                }
                            }
                            token = strtok(NULL, ",");
                        }
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }

    for (size_t i = 0; i < excludes.count; i++) {
        free(excludes.rules[i]);
    }
    free(excludes.rules);

    char *curr_path = get_string_value("PATH");
    if (
        curr_path &&
        *curr_path
    ) {
        append_path_list(
            &new_path,
            curr_path
        );
    }

    if (new_path.str) {
        SHELL_VAR *old_v = find_variable("PATH");
        if (old_v) {
            VUNSETATTR(
                old_v,
                att_readonly
            );
        }

        SHELL_VAR *v = bind_variable(
            "PATH",
            new_path.str,
            0
        );

        if (v) {
            VSETATTR(
                v,
                att_exported
            );

            if (is_readonly) {
                VSETATTR(
                    v,
                    att_readonly
                );
            }
        }
        free(new_path.str);
    }

    return EXECUTION_SUCCESS;
}

#endif

// Copyright (c) 2026 Zeronetsec