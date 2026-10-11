// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_ldconfig_h
#define utils_crawlpath_ldconfig_h

#include <stdio.h>
#include <string.h>
#include <utils/crawlpath/exclude_list.h>
#include <utils/crawlpath/trim.h>
#include <utils/crawlpath/expvar.h>

static inline void ldconfig(
    const char *config_file,
    ExcludeList *ex
) {
    if (!ex || !config_file) {
        return;
    }

    ex->count = 0;
    FILE *fp = fopen(config_file, "r");
    if (!fp) {
        return;
    }

    char line[MAX_PATH_LEN];
    while (fgets(line, sizeof(line), fp)) {
        trim(line);

        if (
            line[0] == '#' ||
            line[0] == '\0'
        ) {
            continue;
        }

        char expanded[MAX_PATH_LEN] = {0};
        expvar(line, expanded, sizeof(expanded));
        trim(expanded);

        if (expanded[0] == '\0') {
            continue;
        }

        size_t len = strlen(expanded);
        while (len > 1 && expanded[len - 1] == '/') {
            expanded[--len] = '\0';
        }

        if (ex->count < MAX_EXCLUDES) {
            snprintf(
                ex->paths[ex->count++],
                MAX_PATH_LEN, "%s",
                expanded
            );
        }
    }
    fclose(fp);
}

#endif

// Copyright (c) 2026 Senzdetta