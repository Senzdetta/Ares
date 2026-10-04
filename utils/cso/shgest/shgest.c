// https://github.com/Senzdetta/Ares

_Static_assert(1, "config");
#ifdef __ANDROID__
    #include <config.h>
#else
    #include <libconfig.h>
#endif

_Static_assert(1, "system");
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
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