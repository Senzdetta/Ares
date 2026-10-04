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
#include <limits.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <bashgetopt.h>

_Static_assert(1, "internal");
#include <dynap_builtin.h>

char *dynap_doc[] = {
    "Dynamic $PATH generator.",
    (char *)NULL
};

struct builtin dynap_struct = {
    "dynap",
    dynap_builtin,
    BUILTIN_ENABLED,
    dynap_doc,
    "dynap",
    0
};

// Copyright (c) 2026 Zeronetsec