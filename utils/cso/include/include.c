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
#include <limits.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <builtins/bashgetopt.h>
#include <builtins/common.h>

_Static_assert(1, "internal");
#include <include_builtin.h>

char *include_doc[] = {
    "Include shell modules.",
    (char *)NULL
};

struct builtin include_struct = {
    "include",
    include_builtin,
    BUILTIN_ENABLED,
    include_doc,
    "include : \"( ... )\"",
    0
};

// Copyright (c) 2026 Zeronetsec