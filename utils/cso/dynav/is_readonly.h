// https://github.com/Senzdetta/Ares

#ifndef is_readonly_h
#define is_readonly_h

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static inline int is_readonly(const char *aresroot) {
    if (!aresroot || !*aresroot) {
        return 0;
    }

    char conf_path[PATH_MAX];
    char *config_dir = get_string_value("__config__");
    if (config_dir && *config_dir) {
        snprintf(
            conf_path, sizeof(conf_path),
            "%s/startup.conf",
            config_dir
        );
    } else {
        snprintf(
            conf_path, sizeof(conf_path),
            "%s/config/startup.conf",
            aresroot
        );
    }

    FILE *fp = fopen(conf_path, "r");
    if (!fp) {
        return 0;
    }

    char line[512];
    int lock_enabled = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *p = line;

        while (*p && isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == '\0' || *p == '#') {
            continue;
        }

        if (strncmp(p, "lock_variable", 13) == 0) {
            p += 13;
            while (*p && isspace((unsigned char)*p)) {
                p++;
            }

            if (*p == '=') {
                p++;

                while (*p && isspace((unsigned char)*p)) {
                    p++;
                }

                if (strncasecmp(p, "true", 4) == 0) {
                    char next = p[4];
                    if (
                        next == '\0' ||
                        isspace((unsigned char)next) ||
                        next == '#'
                    ) {
                        lock_enabled = 1;
                        break;
                    }
                }
            }
        }
    }

    fclose(fp);
    return lock_enabled;
}

#endif

// Copyright (c) 2026 Senzdetta