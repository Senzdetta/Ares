// https://github.com/Senzdetta/Ares

#ifndef parse_startup_conf_h
#define parse_startup_conf_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

_Static_assert(1, "internal");
#include <registered_engine_t.h>
#include <strip_slashes.h>

static inline bool parse_startup_conf(
    const char *conf_file_path,
    registered_engine_t *reg
) {
    FILE *fp = fopen(conf_file_path, "r");
    if (!fp) {
        return false;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *comment = strstr(line, "#");
        if (comment) {
            *comment = '\0';
        }

        char *eq = strstr(line, "=");
        if (!eq) {
            continue;
        }

        *eq = '\0';
        char *key = line;
        char *value = eq + 1;

        while (
            *key == ' ' ||
            *key == '\t' ||
            *key == '\r' ||
            *key == '\n'
        ) {
            key++;
        }

        char *key_end = key + strlen(key) - 1;
        while (
            key_end > key &&
            (
                *key_end == ' ' ||
                *key_end == '\t' ||
                *key_end == '\r' ||
                *key_end == '\n'
            )
        ) {
            *key_end = '\0';
            key_end--;
        }

        size_t klen = strlen(key);
        if (
            klen < 7 ||
            strcmp(key + klen - 7, "_engine") != 0
        ) {
            continue;
        }

        char category[256];
        size_t cat_len = klen - 7;
        if (cat_len >= sizeof(category)) {
            continue;
        }

        strncpy(category, key, cat_len);
        category[cat_len] = '\0';

        while (
            *value == ' ' ||
            *value == '\t' ||
            *value == '\r' ||
            *value == '\n'
        ) {
            value++;
        }

        char *val_end = value + strlen(value) - 1;
        while (
            val_end > value &&
            (
                *val_end == ' ' ||
                *val_end == '\t' ||
                *val_end == '\r' ||
                *val_end == '\n'
            )
        ) {
            *val_end = '\0';
            val_end--;
        }

        if (strlen(value) > 0 && strlen(category) > 0) {
            char combined[512];
            snprintf(
                combined, sizeof(combined),
                "%s/%s",
                category, value
            );

            if (reg->count >= reg->cap) {
                reg->cap = (reg->cap == 0) ?
                    16 :
                    reg->cap * 2;

                reg->paths = realloc(
                    reg->paths,
                    reg->cap * sizeof(char *)
                );
            }

            reg->paths[reg->count++] = strdup(combined);
        }
    }
    fclose(fp);
    return true;
}

#endif

// Copyright (c) 2026 Senzdetta