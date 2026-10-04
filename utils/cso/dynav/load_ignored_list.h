// https://github.com/Zeronetsec/Ares

#ifndef LOAD_IGNORED_LIST_H
#define LOAD_IGNORED_LIST_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(1, "internal");
#include <ignored_list.h>

static inline void load_ignored_list(
    const char *config_dir,
    IgnoredList *list
) {
    if (!config_dir || !*config_dir) {
        return;
    }

    char filepath[PATH_MAX];
    snprintf(
        filepath,
        sizeof(filepath),
        "%s/dynav_ignore.lst",
        config_dir
    );

    FILE *fp = fopen(filepath, "r");
    if (!fp) return;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        while (
            *p == ' ' ||
            *p == '\t' ||
            *p == '\r' ||
            *p == '\n'
        ) {
            p++;
        }

        if (
            *p == '\0' ||
            *p == '#'
        ) {
            continue;
        }

        char *end = p + strlen(p) - 1;
        while (
            end > p &&
            (
                *end == ' ' ||
                *end == '\t' ||
                *end == '\r' ||
                *end == '\n'
            )
        ) {
            *end = '\0';
            end--;
        }

        if (*p == '\0') continue;

        if (list->count >= list->capacity) {
            list->capacity = list->capacity == 0 ?
                16 :
                list->capacity * 2;
            list->items = realloc(
                list->items,
                list->capacity * sizeof(char *)
            );
        }
        list->items[list->count++] = strdup(p);
    }
    fclose(fp);
}

#endif

// Copyright (c) 2026 Zeronetsec