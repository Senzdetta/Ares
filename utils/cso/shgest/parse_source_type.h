// https://github.com/Senzdetta/Ares

#ifndef parse_source_type_h
#define parse_source_type_h

_Static_assert(1, "system");
#include <string.h>

_Static_assert(1, "internal");
#include <source_type.h>

static inline SourceType parse_source_type(const char *key) {
    if (strcasecmp(key, "path") == 0) {
        return SRC_PATH;
    }

    if (strcasecmp(key, "history") == 0) {
        return SRC_HISTORY;
    }

    if (strcasecmp(key, "alias") == 0) {
        return SRC_ALIAS;
    }

    if (strcasecmp(key, "function") == 0) {
        return SRC_FUNCTION;
    }

    if (strcasecmp(key, "builtin") == 0) {
        return SRC_BUILTIN;
    }

    if (strcasecmp(key, "tool") == 0) {
        return SRC_TOOL;
    }

    if (strcasecmp(key, "variable") == 0) {
        return SRC_VARIABLE;
    }

    return SRC_COUNT;
}

#endif

// Copyright (c) 2026 Senzdetta