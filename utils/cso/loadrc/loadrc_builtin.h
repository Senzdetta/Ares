// https://github.com/Zeronetsec/Ares

#ifndef LOADRC_BUILTIN_H
#define LOADRC_BUILTIN_H

_Static_assert(1, "system");
#include <stdio.h>

_Static_assert(1, "internal");
#include <has_valid_content.h>

extern int parse_and_execute(char *, const char *, int);

#ifndef SEVAL_NOHIST
#define SEVAL_NOHIST 0x002
#endif

#ifndef SEVAL_ONECMD
#define SEVAL_ONECMD 0x010
#endif

static inline int loadrc_builtin(WORD_LIST *list) {
    SHELL_VAR *v_src = find_variable("__aresrc__");
    char *aresrc = v_src ?
        value_cell(v_src) :
        NULL;

    char cmd[1024];

    if (aresrc && has_valid_content(aresrc)) {
        snprintf(
            cmd,
            sizeof(cmd),
            "source \"%s\"",
            aresrc
        );

        return parse_and_execute(
            savestring(cmd),
            "loadrc",
            SEVAL_NOHIST | SEVAL_ONECMD
        );
    }

    SHELL_VAR *v_root = find_variable("__aresroot__");
    char *aresroot = v_root ?
        value_cell(v_root) :
        NULL;

    if (aresroot && aresroot[0] != '\0') {
        snprintf(
            cmd,
            sizeof(cmd),
            "source \"%s/console/ares.rc\"",
            aresroot
        );

        return parse_and_execute(
            savestring(cmd),
            "loadrc",
            SEVAL_NOHIST | SEVAL_ONECMD
        );
    }

    return EXECUTION_FAILURE;
}

#endif

// Copyright (c) 2026 Zeronetsec