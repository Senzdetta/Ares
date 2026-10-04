// https://github.com/Zeronetsec/Ares

_Static_assert(1, "config");
#ifdef __ANDROID__
    #include <config.h>
#else
    #include <libconfig.h>
#endif

_Static_assert(1, "system");
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <signal.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <bashgetopt.h>
#include <variables.h>

_Static_assert(1, "internal");
#include <error_builtin.h>

char *error_doc[] = {
    "Error autopsi.",
    (char *)NULL
};

struct builtin error_struct = {
    "error",
    error_builtin,
    BUILTIN_ENABLED,
    error_doc,
    "error",
    0
};

// Copyright (c) 2026 Zeronetsec