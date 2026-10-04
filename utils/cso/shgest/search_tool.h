// https://github.com/Zeronetsec/Ares

#ifndef SEARCH_TOOL_H
#define SEARCH_TOOL_H

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static inline char *search_tool(
    const char *input,
    size_t len
) {
    const char *last_word = strrchr(input, ' ');
    if (last_word) {
        last_word++;
    } else {
        last_word = input;
    }

    size_t wlen = strlen(last_word);
    if (wlen == 0) {
        return NULL;
    }

    char *path_env = getenv("PATH");
    if (!path_env) {
        return NULL;
    }

    char *path_copy = strdup(path_env);
    char *dir = strtok(path_copy, ":");
    char *res = NULL;

    while (dir != NULL) {
        DIR *dp = opendir(dir);
        if (dp) {
            struct dirent *entry;
            while ((entry = readdir(dp)) != NULL) {
                if (
                    strncmp(entry->d_name, last_word, wlen) == 0 &&
                    strlen(entry->d_name) > wlen
                ) {
                    size_t prefix_len = last_word - input;
                    size_t full_len = prefix_len +
                        strlen(entry->d_name) +
                        1;

                    res = malloc(full_len);
                    if (res) {
                        strncpy(res, input, prefix_len);
                        res[prefix_len] = '\0';
                        strcat(res, entry->d_name);
                    }
                    closedir(dp);
                    free(path_copy);
                    return res;
                }
            }
            closedir(dp);
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

#endif

// Copyright (c) 2026 Zeronetsec