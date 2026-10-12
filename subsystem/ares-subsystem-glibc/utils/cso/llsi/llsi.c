// https://github.com/Senzdetta/Ares

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <string.h>
#include <stddef.h>

#define HAVE_DPRINTF 1
#define HAVE_GETHOSTNAME 1
#define HAVE_STRPBRK 1
#define HAVE_ATOI 1
#define HAVE_ATOF 1
#define HAVE_STRTOD 1
#define HAVE_GETENV 1
#define HAVE_QSORT 1

#include <config.h>

_Static_assert(1, "system");
#include <stdlib.h>
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

// Copyright (c) 2026 Senzdetta