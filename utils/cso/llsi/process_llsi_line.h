// https://github.com/Senzdetta/Ares

#ifndef PROCESS_LLSI_LINE_H
#define PROCESS_LLSI_LINE_H

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

extern int parse_and_execute(char *, const char *, int);

#ifndef SEVAL_NONINT
#define SEVAL_NONINT 0x001
#endif

#ifndef SEVAL_NOHIST
#define SEVAL_NOHIST 0x002
#endif

static inline void process_llsi_line(
    char *line,
    char *current_block,
    size_t block_size,
    int *in_block,
    const char *aresroot,
    size_t root_len
) {
    char *ptr = line;
    while (
        *ptr == ' ' ||
        *ptr == '\t' ||
        *ptr == '\n' ||
        *ptr == '\r'
    ) {
        ptr++;
    }

    if (
        *ptr == '\0' ||
        (ptr[0] == '/' && ptr[1] == '/')
    ) {
        return;
    }

    if (*ptr == '}') {
        *in_block = 0;
        current_block[0] = '\0';
        return;
    }

    char *brace = strchr(ptr, '{');
    if (brace) {
        *brace = '\0';
        char *end = brace - 1;
        while (
            end >= ptr &&
            (
                *end == ' ' ||
                *end == '\t'
            )
        ) {
            *end-- = '\0';
        }

        strncpy(
            current_block,
            ptr,
            block_size - 1
        );

        current_block[block_size - 1] = '\0';
        *in_block = 1;
        return;
    }

    if (*in_block) {
        char *arrow = strstr(ptr, "->");
        if (arrow) {
            *arrow = '\0';
            char *key = ptr;
            char *val = arrow + 2;

            char *end = arrow - 1;
            while (
                end >= key &&
                (
                    *end == ' ' ||
                    *end == '\t'
                )
            ) {
                *end-- = '\0';
            }

            while (
                *val == ' ' ||
                *val == '\t'
            ) {
                val++;
            }

            size_t vlen = strlen(val);
            if (vlen > 0) {
                char *vend = val + vlen - 1;
                while (
                    vend >= val &&
                    (
                        *vend == ' ' ||
                        *vend == '\t' ||
                        *vend == '\n' ||
                        *vend == '\r'
                    )
                ) {
                    *vend-- = '\0';
                }
            }

            if (*val == '\0') return;

            char target_path[2048];
            if (
                aresroot[root_len - 1] == '/' ||
                val[0] == '/'
            ) {
                snprintf(
                    target_path,
                    sizeof(target_path),
                    "%s%s",
                    aresroot,
                    val
                );
            } else {
                snprintf(
                    target_path,
                    sizeof(target_path),
                    "%s/%s",
                    aresroot,
                    val
                );
            }

            struct stat st;
            if (stat(target_path, &st) == 0) {
                char cmd[4096];
                snprintf(
                    cmd,
                    sizeof(cmd),
                    "source \"%s\"",
                    target_path
                );

                parse_and_execute(
                    savestring(cmd),
                    "llsi_builtin",
                    SEVAL_NONINT | SEVAL_NOHIST
                );
            } else {
                printf(
                    "%s[!] %sLlsi: %s%s %sfrom %s%s %sin %s%s %snot found!\n",
                    color_R, color_N, color_GG, val, color_N,
                    color_CC, current_block, color_N,
                    color_YY, key, color_N
                );
            }
        }
    }
}

#endif

// Copyright (c) 2026 Senzdetta