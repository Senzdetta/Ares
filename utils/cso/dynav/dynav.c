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
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <builtins.h>
#include <shell.h>
#include <bashgetopt.h>

_Static_assert(1, "internal");
#include <dynav_builtin.h>

char *dynav_doc[] = {
    "Dynamic $__var__ exporter.",
    (char *)NULL
};

struct builtin dynav_struct = {
    "dynav",
    dynav_builtin,
    BUILTIN_ENABLED,
    dynav_doc,
    "dynav",
    0
};

// Copyright (c) 2026 Senzdetta