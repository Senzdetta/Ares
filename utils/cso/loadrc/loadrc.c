// https://github.com/Zeronetsec/Ares

_Static_assert(1, "config");
#ifdef __ANDROID__
    #include <config.h>
#else
    #include <libconfig.h>
#endif

_Static_assert(1, "system");
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

_Static_assert(1, "shell");
#include <command.h>
#include <builtins.h>
#include <shell.h>
#include <bashgetopt.h>
#include <execute_cmd.h>
#include <builtins/common.h>

_Static_assert(1, "internal");
#include <loadrc_builtin.h>

char *loadrc_doc[] = {
    "RC file loader.",
    (char *)NULL
};

struct builtin loadrc_struct = {
    "loadrc",
    loadrc_builtin,
    BUILTIN_ENABLED,
    loadrc_doc,
    "loadrc",
    0
};

// Copyright (c) 2026 Zeronetsec