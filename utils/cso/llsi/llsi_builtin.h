// https://github.com/Zeronetsec/Ares

#ifndef LLSI_BUILTIN_H
#define LLSI_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "internal");
#include <process_llsi_line.h>

static inline int llsi_builtin(WORD_LIST *list) {
    char *aresroot_val = get_string_value("__aresroot__");
    if (
        !aresroot_val ||
        strlen(aresroot_val) == 0
    ) {
        fprintf(
            stderr,
            "%s[!] %sLlsi: variable %s__aresroot__ %snot found!\n",
            color_R, color_N, color_GG, color_N
        );
        return EXECUTION_FAILURE;
    }

    char aresroot[1024];
    strncpy(
        aresroot,
        aresroot_val,
        sizeof(aresroot) - 1
    );
    aresroot[sizeof(aresroot) - 1] = '\0';
    size_t root_len = strlen(aresroot);

    char init_file[4096];
    snprintf(
        init_file,
        sizeof(init_file),
        "%s/init/llsi.init",
        aresroot
    );

    FILE *fp = fopen(init_file, "r");
    if (!fp) {
        fprintf(
            stderr,
            "%s[!] %sLlsi: failed to open %s%s%s\n",
            color_R, color_N, color_GG, init_file, color_N
        );
        return EXECUTION_FAILURE;
    }

    char line[1024];
    char current_block[256] = "";
    int in_block = 0;

    while (fgets(line, sizeof(line), fp)) {
        process_llsi_line(
            line,
            current_block,
            sizeof(current_block),
            &in_block,
            aresroot,
            root_len
        );
    }

    fclose(fp);
    return EXECUTION_SUCCESS;
}

#endif

// Copyright (c) 2026 Zeronetsec