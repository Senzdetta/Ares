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
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <builtins/bashgetopt.h>
#include <builtins/common.h>

_Static_assert(1, "internal");
#include <loadso_builtin.h>

char *loadso_doc[] = {
    "Load cso.",
    (char *)NULL
};

struct builtin loadso_struct = {
    "loadso",
    loadso_builtin,
    BUILTIN_ENABLED,
    loadso_doc,
    "loadso : \"( ... )\"",
    0
};

// Copyright (c) 2026 Senzdetta