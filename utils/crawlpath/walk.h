// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_walk_h
#define utils_crawlpath_walk_h

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <utils/crawlpath/exclude_list.h>
#include <utils/crawlpath/excluded.h>

static inline void walk(
    const char *current_dir,
    const char *rel_prefix,
    const ExcludeList *ex,
    char *out_buf,
    size_t out_size
) {
    if (!current_dir || !rel_prefix || !out_buf) {
        return;
    }

    if (excluded(rel_prefix, ex)) {
        return;
    }

    size_t cur_len = strlen(out_buf);
    if (cur_len > 0) {
        snprintf(
            out_buf + cur_len,
            out_size - cur_len,
            ":%s", current_dir
        );
    } else {
        snprintf(
            out_buf, out_size,
            "%s", current_dir
        );
    }

    DIR *dir = opendir(current_dir);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        char full_path[MAX_PATH_LEN];
        char rel_path[MAX_PATH_LEN];

        snprintf(
            full_path, sizeof(full_path),
            "%s/%s",
            current_dir, entry->d_name
        );

        snprintf(
            rel_path, sizeof(rel_path),
            "%s/%s",
            rel_prefix, entry->d_name
        );

        struct stat st;
        if (
            stat(full_path, &st) == 0 &&
            S_ISDIR(st.st_mode)
        ) {
            walk(
                full_path, rel_path,
                ex,
                out_buf, out_size
            );
        }
    }
    closedir(dir);
}

#endif

// Copyright (c) 2026 Senzdetta