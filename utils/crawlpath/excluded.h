// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_excluded_h
#define utils_crawlpath_excluded_h

#include <string.h>
#include <utils/crawlpath/exclude_list.h>

static inline int excluded(
    const char *rel_path,
    const ExcludeList *ex
) {
    if (!rel_path || !ex) {
        return 0;
    }

    for (int i = 0; i < ex->count; i++) {
        size_t rlen = strlen(ex->paths[i]);
        size_t plen = strlen(rel_path);

        if (strcmp(rel_path, ex->paths[i]) == 0) {
            return 1;
        }

        if (plen <= rlen) {
            if (
                strcmp(
                    ex->paths[i] + (rlen - plen),
                    rel_path
                ) == 0
            ) {
                if (
                    rlen == plen ||
                    ex->paths[i][rlen - plen - 1] == '/'
                ) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta