// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_crawler_h
#define utils_crawlpath_crawler_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/variable.h>
#include <utils/crawlpath/exclude_list.h>
#include <utils/crawlpath/ldconfig.h>
#include <utils/crawlpath/walk.h>

static inline int crawler(void) {
    const char *root = __aresroot__;
    if (!root || strlen(root) == 0) {
        return -1;
    }

    char cfg_path[MAX_PATH_LEN];
    snprintf(
        cfg_path, sizeof(cfg_path),
        "%s/config/dynap_exclude.lst",
        root
    );

    ExcludeList ex;
    ldconfig(cfg_path, &ex);

    char base_bin[MAX_PATH_LEN];
    snprintf(
        base_bin, sizeof(base_bin),
        "%s/bin",
        root
    );

    char crawled_paths[PATH_BUF_SIZE] = {0};
    walk(
        base_bin, "bin", &ex,
        crawled_paths, sizeof(crawled_paths)
    );

    const char *old_path = getenv("PATH");
    char final_path[PATH_BUF_SIZE * 2] = {0};

    if (
        strlen(crawled_paths) > 0 &&
        old_path &&
        strlen(old_path) > 0
    ) {
        snprintf(
            final_path, sizeof(final_path),
            "%s:%s",
            crawled_paths, old_path
        );
    } else if (strlen(crawled_paths) > 0) {
        snprintf(
            final_path, sizeof(final_path),
            "%s",
            crawled_paths
        );
    } else if (old_path) {
        snprintf(
            final_path, sizeof(final_path),
            "%s",
            old_path
        );
    }

    char clean_path[PATH_BUF_SIZE * 2] = {0};
    char *src = final_path;
    char *dst = clean_path;

    int last_was_colon = 0;

    while (*src) {
        if (*src == ':') {
            if (!last_was_colon && dst != clean_path) {
                *dst++ = ':';
                last_was_colon = 1;
            }
        } else {
            *dst++ = *src;
            last_was_colon = 0;
        }
        src++;
    }

    if (dst > clean_path && *(dst - 1) == ':') {
        dst--;
    }
    *dst = '\0';

    return setenv(
        "PATH", clean_path, 1
    );
}

#endif

// Copyright (c) 2026 Senzdetta