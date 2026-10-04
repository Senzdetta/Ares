// https://github.com/Senzdetta/Ares

_Static_assert(1, "config");
#ifdef __ANDROID__
    #include <config.h>
#else
    #include <libconfig.h>
#endif

_Static_assert(1, "system");
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>

_Static_assert(1, "internal");
#include <catchypr_builtin.h>

char *catchypr_doc[] = {
    "Dynamic PS1 generator.",
    (char *)NULL
};

struct builtin catchypr_struct = {
    "catchypr",
    catchypr_builtin,
    1,
    catchypr_doc,
    "catchypr",
    0
};

// Copyright (c) 2026 Senzdetta