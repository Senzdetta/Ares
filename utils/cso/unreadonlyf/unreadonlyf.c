// https://github.com/Senzdetta/Ares

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

_Static_assert(1, "internal");
#include <unreadonlyf_builtin.h>

char *unreadonlyf_doc[] = {
    "Removes readonly attribute from functions inside block.",
    (char *)NULL
};

struct builtin unreadonlyf_struct = {
    "unreadonlyf",
    unreadonlyf_builtin,
    BUILTIN_ENABLED,
    unreadonlyf_doc,
    "unreadonlyf : \"( ... )\"",
    0
};

// Copyright (c) 2026 Senzdetta