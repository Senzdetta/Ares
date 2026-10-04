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
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <shell.h>
#include <builtins.h>
#include <execute_cmd.h>
#include <builtins/common.h>

_Static_assert(1, "internal");
#include <llsi_builtin.h>

char *llsi_doc[] = {
    "Loads lib shell init.",
    (char *)NULL
};

struct builtin llsi_struct = {
    "llsi",
    llsi_builtin,
    BUILTIN_ENABLED,
    llsi_doc,
    "llsi",
    0
};

// Copyright (c) 2026 Zeronetsec