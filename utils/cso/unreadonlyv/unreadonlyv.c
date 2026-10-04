// https://github.com/Zeronetsec/Ares

_Static_assert(1, "config");
#ifdef __ANDROID__
    #include <config.h>
#else
    #include <libconfig.h>
#endif

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <variables.h>

_Static_assert(1, "system");
#include <unreadonlyv_builtin.h>

char *unreadonlyv_doc[] = {
    "Removes readonly attribute from variables inside block.",
    (char *)NULL
};

struct builtin unreadonlyv_struct = {
    "unreadonlyv",
    unreadonlyv_builtin,
    BUILTIN_ENABLED,
    unreadonlyv_doc,
    "unreadonlyv : \"( ... )\"",
    0
};

// Copyright (c) 2026 Zeronetsec