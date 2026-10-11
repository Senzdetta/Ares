// https://github.com/Senzdetta/Ares

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stddef.h>
#include <wchar.h>
#include <string.h>

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
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/stat.h>

_Static_assert(1, "shell");
#include <command.h>
#include <general.h>
#include <error.h>
#include <variables.h>
#include <arrayfunc.h>
#include <quit.h>
#include <builtins.h>
#include <shell.h>

_Static_assert(1, "readline");
#include <readline/readline.h>
#include <readline/history.h>

_Static_assert(1, "internal");
#include <shgest_builtin.h>

char *shgest_doc[] = {
    "Shell auto-suggestion config bassed.",
    (char *)NULL
};

struct builtin shgest_struct = {
    "shgest",
    shgest_builtin,
    BUILTIN_ENABLED,
    shgest_doc,
    "shgest",
    0
};

// Copyright (c) 2026 Senzdetta