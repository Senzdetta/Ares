// https://github.com/Senzdetta/Ares

#ifndef search_path_h
#define search_path_h

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

_Static_assert(1, "internal");
#include <expand_env.h>

static inline char *search_path(
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

    char *expanded_word = expand_env(last_word);
    if (!expanded_word) {
        return NULL;
    }

    char *slash = strrchr(expanded_word, '/');
    char dir_to_open[1024] = ".";
    const char *prefix_filter = expanded_word;

    if (slash) {
        size_t dir_len = slash - expanded_word;
        if (dir_len == 0) {
            snprintf(
                dir_to_open, sizeof(dir_to_open),
                "/"
            );
        } else {
            snprintf(
                dir_to_open, sizeof(dir_to_open),
                "%.*s", (int)dir_len, expanded_word
            );
        }
        prefix_filter = slash + 1;
    }

    DIR *dp = opendir(dir_to_open);
    if (!dp) {
        free(expanded_word);
        return NULL;
    }

    size_t flen = strlen(prefix_filter);
    struct dirent *entry;
    char *res = NULL;

    while ((entry = readdir(dp)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        if (strncmp(entry->d_name, prefix_filter, flen) == 0) {
            if (strlen(entry->d_name) > flen) {
                size_t prefix_len = last_word - input;
                const char *orig_slash = strrchr(last_word, '/');

                size_t dir_part_len = orig_slash ?
                    (size_t)(orig_slash - last_word + 1) :
                    0;

                size_t total_len = prefix_len +
                    dir_part_len +
                    strlen(entry->d_name) +
                    1;

                res = malloc(total_len);
                if (res) {
                    strncpy(res, input, prefix_len);
                    res[prefix_len] = '\0';

                    if (dir_part_len > 0) {
                        strncat(res, last_word, dir_part_len);
                    }

                    strcat(res, entry->d_name);
                }
                break;
            }
        }
    }

    closedir(dp);
    free(expanded_word);
    return res;
}

#endif

// Copyright (c) 2026 Senzdetta