// https://github.com/Senzdetta/Ares

#ifndef load_active_engines_h
#define load_active_engines_h

#include <stdio.h>
#include <string.h>
#include <active_engine.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

static inline void load_active_engines(
    const char *aresroot,
    ActiveEngine *active_engines,
    int *active_count
) {
    char config_path[MAX_PATH];
    snprintf(
        config_path, sizeof(config_path),
        "%s/config/startup.conf",
        aresroot
    );

    FILE *f = fopen(config_path, "r");
    if (!f) {
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') {
            p++;
        }

        if (
            *p == '#' ||
            *p == '\n' ||
            *p == '\r' ||
            *p == '\0'
        ) {
            continue;
        }

        char *engine_pos = strstr(p, "_engine");
        if (engine_pos) {
            *engine_pos = '\0';
            char *category = p;

            char *eq = strchr(engine_pos + 7, '=');
            if (eq) {
                eq++;
                while (*eq == ' ' || *eq == '\t') {
                    eq++;
                }

                char *val_end = eq;
                while (
                    *val_end &&
                    *val_end != '\n' &&
                    *val_end != '\r' &&
                    *val_end != ' ' &&
                    *val_end != '\t'
                ) {
                    val_end++;
                }

                *val_end = '\0';

                char *cat_end = category + strlen(category) - 1;
                while (
                    cat_end > category &&
                    (
                        *cat_end == ' ' ||
                        *cat_end == '\t'
                    )
                ) {
                    *cat_end-- = '\0';
                }

                if (*active_count < 100) {
                    strncpy(
                        active_engines[*active_count].category,
                        category, 255
                    );

                    strncpy(
                        active_engines[*active_count].name,
                        eq, 255
                    );

                    (*active_count)++;
                }
            }
        }
    }
    fclose(f);
}

#endif

// Copyright (c) 2026 Senzdetta