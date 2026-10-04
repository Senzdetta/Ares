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
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <builtins/common.h>

_Static_assert(1, "internal");
#include <shmod_builtin.h>

char *shmod_doc[] = {
    "Load modular shell script.",
    (char *)NULL
};

struct builtin shmod_struct = {
    "shmod",
    shmod_builtin,
    BUILTIN_ENABLED,
    shmod_doc,
    "shmod",
    0
};

// Copyright (c) 2026 Zeronetsec