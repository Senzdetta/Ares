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

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <bashgetopt.h>

_Static_assert(1, "internal");
#include <rhome_builtin.h>

char *rhome_doc[] = {
    "Dynamic $HOME resolver.",
    (char *)NULL
};

struct builtin rhome_struct = {
    "rhome",
    rhome_builtin,
    BUILTIN_ENABLED,
    rhome_doc,
    "rhome",
    0
};

// Copyright (c) 2026 Senzdetta