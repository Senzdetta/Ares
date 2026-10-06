// https://github.com/Senzdetta/Ares

#ifndef read_current_theme_h
#define read_current_theme_h

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>

_Static_assert(1, "internal");
#include <get_config.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#ifndef MAX_LINE
#define MAX_LINE 512
#endif

static inline int read_current_theme(char *out_theme, size_t size) {
    char config_path[MAX_PATH];
    get_config(config_path, sizeof(config_path));

    FILE *f = fopen(config_path, "r");
    if (!f) return 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') {
            ptr++;
        }

        if (strncmp(ptr, "yumipr_theme", 12) == 0) {
            char *eq = strchr(ptr, '=');
            if (eq) {
                eq++;

                while (*eq == ' ' || *eq == '\t') {
                    eq++;
                }

                strncpy(out_theme, eq, size - 1);
                out_theme[size - 1] = '\0';

                size_t len = strlen(out_theme);
                while (
                    len > 0 &&
                    (
                        out_theme[len - 1] == '\r' || 
                        out_theme[len - 1] == '\n' || 
                        out_theme[len - 1] == ' '  || 
                        out_theme[len - 1] == '\t'
                    )
                ) {
                    out_theme[len - 1] = '\0';
                    len--;
                }
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta