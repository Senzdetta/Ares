// https://github.com/Zeronetsec/Ares

#ifndef utils_embeded_shell_h
#define utils_embeded_shell_h

_Static_assert(1, "system");
#include <stddef.h>

static const unsigned char embeded_shell[] = {
    #include <utils/embeded/shell.h>
};

static const size_t embeded_shell_size = sizeof(embeded_shell);

#endif

// Copyright (c) 2026 Zeronetsec