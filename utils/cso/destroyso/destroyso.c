// https://github.com/Zeronetsec/Ares

_Static_assert(1, "config");
#ifdef __ANDROID__
    #include <config.h>
#else
    #include <libconfig.h>
#endif

_Static_assert(1, "system");
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <builtins/bashgetopt.h>
#include <builtins/common.h>

_Static_assert(1, "internal");
#include <destroyso_builtin.h>

char *destroyso_doc[] = {
    "Unload cso.",
    (char *)NULL
};

struct builtin destroyso_struct = {
    "destroyso",
    destroyso_builtin,
    BUILTIN_ENABLED,
    destroyso_doc,
    "destroyso : \"( ... )\"",
    0
};

// Copyright (c) 2026 Zeronetsec