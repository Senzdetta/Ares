// https://github.com/Zeronetsec/Ares

#ifndef TRAVERSE_AND_FIND_DIRS_H
#define TRAVERSE_AND_FIND_DIRS_H

_Static_assert(1, "system");
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "internal");
#include <exclude_list.h>
#include <string_buffer.h>
#include <is_excluded.h>
#include <append_path.h>

static inline void traverse_and_find_dirs(
    const char *dirpath,
    StringBuffer *sb,
    ExcludeList *excludes
) {
    if (!dirpath || !*dirpath) {
        return;
    }

    if (is_excluded(dirpath, excludes)) {
        return;
    }

    append_path(sb, dirpath);

    DIR *dir = opendir(dirpath);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    char childpath[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        snprintf(
            childpath,
            sizeof(childpath),
            "%s/%s",
            dirpath, entry->d_name
        );

        int is_dir = 0;
        #ifdef _DIRENT_HAVE_D_TYPE
            if (entry->d_type != DT_UNKNOWN) {
                is_dir = (entry->d_type == DT_DIR);
            } else
        #endif
        {
            struct stat st;
            if (
                stat(childpath, &st) == 0 &&
                S_ISDIR(st.st_mode)
            ) {
                is_dir = 1;
            }
        }

        if (is_dir) {
            traverse_and_find_dirs(
                childpath,
                sb,
                excludes
            );
        }
    }
    closedir(dir);
}

#endif

// Copyright (c) 2026 Zeronetsec