// https://github.com/Senzdetta/Ares

#ifndef LOAD_CONFIG_H
#define LOAD_CONFIG_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

_Static_assert(1, "internal");
#include <source_type.h>
#include <shgest_state.h>
#include <trim_whitespace.h>
#include <parse_source_type.h>
#include <unescape_str.h>

static inline void load_config(void) {
    SourceType default_order[] = {
        SRC_PATH,
        SRC_HISTORY,
        SRC_ALIAS,
        SRC_FUNCTION,
        SRC_BUILTIN,
        SRC_TOOL,
        SRC_VARIABLE
    };

    priority_count = SRC_COUNT;
    for (int i = 0; i < SRC_COUNT; i++) {
        priority_order[i] = default_order[i];
        priority_enabled[i] = 1;
    }

    snprintf(
        cutter_symbol, sizeof(cutter_symbol),
        "..."
    );

    snprintf(
        cutter_color, sizeof(cutter_color),
        "\x1b[1;31m"
    );

    snprintf(
        other_color, sizeof(other_color),
        "\x1b[1;90m"
    );

    char config_path[1024] = {0};
    char *env_config = getenv("__config__");
    if (env_config && strlen(env_config) > 0) {
        snprintf(
            config_path,
            sizeof(config_path),
            "%s/shgest.conf",
            env_config
        );
    }

    FILE *file = fopen(config_path, "r");
    if (!file) {
        return;
    }

    int custom_count = 0;
    int visited[SRC_COUNT] = {0};
    char line[512];

    while (fgets(line, sizeof(line), file)) {
        char *trimmed = trim_whitespace(line);
        if (trimmed[0] == '#' || trimmed[0] == '\0') {
            continue;
        }

        char *eq = strchr(trimmed, '=');
        if (!eq) {
            continue;
        }

        *eq = '\0';
        char *key = trim_whitespace(trimmed);
        char *val = trim_whitespace(eq + 1);

        if (strcasecmp(key, "cutter_symbol") == 0) {
            unescape_str(
                cutter_symbol, val, sizeof(cutter_symbol)
            );
            continue;
        }

        if (strcasecmp(key, "cutter_color") == 0) {
            unescape_str(
                cutter_color, val, sizeof(cutter_color)
            );
            continue;
        }

        if (strcasecmp(key, "other_color") == 0) {
            unescape_str(
                other_color, val, sizeof(other_color)
            );
            continue;
        }

        char *color_suffix = strstr(key, "_color");
        if (
            color_suffix &&
            strcmp(color_suffix, "_color") == 0
        ) {
            char prefix[64] = {0};
            size_t prefix_len = color_suffix - key;
            if (prefix_len < sizeof(prefix)) {
                strncpy(prefix, key, prefix_len);
                prefix[prefix_len] = '\0';
                SourceType st = parse_source_type(prefix);
                if (st != SRC_COUNT) {
                    unescape_str(
                        source_colors[st], val,
                        sizeof(source_colors[st])
                    );
                    continue;
                }
            }
        }

        SourceType st = parse_source_type(key);
        if (st != SRC_COUNT && !visited[st]) {
            visited[st] = 1;

            int bool_val = (
                strcasecmp(val, "true") == 0 ||
                strcmp(val, "1") == 0
            );

            priority_order[custom_count] = st;
            priority_enabled[st] = bool_val;
            custom_count++;
        }
    }

    for (int i = 0; i < SRC_COUNT; i++) {
        if (!visited[i]) {
            priority_order[custom_count] = (SourceType)i;
            priority_enabled[i] = 0;
            custom_count++;
        }
    }

    priority_count = custom_count;
    fclose(file);
}

#endif

// Copyright (c) 2026 Senzdetta