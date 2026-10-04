// https://github.com/Senzdetta/Ares

#ifndef FIND_MATCH_H
#define FIND_MATCH_H

_Static_assert(1, "internal");
#include <shgest_state.h>
#include <source_type.h>
#include <search_path.h>
#include <search_history.h>
#include <search_alias.h>
#include <search_function.h>
#include <search_variable.h>
#include <search_builtin.h>
#include <search_tool.h>

static inline char *find_match(const char *input, size_t len) {
    for (int i = 0; i < priority_count; i++) {
        SourceType st = priority_order[i];
        if (!priority_enabled[st]) {
            continue;
        }

        char *match = NULL;
        switch (st) {
            case SRC_PATH:
                match = search_path(input, len);
                break;
            case SRC_HISTORY:
                match = search_history(input, len);
                break;
            case SRC_ALIAS:
                match = search_alias(input, len);
                break;
            case SRC_FUNCTION:
                match = search_function(input, len);
                break;
            case SRC_VARIABLE:
                match = search_variable(input, len);
                break;
            case SRC_BUILTIN:
                match = search_builtin(input, len);
                break;
            case SRC_TOOL:
                match = search_tool(input, len);
                break;
            default:
                break;
        }
        if (match) {
            last_matched_source = st;
            return match;
        }
    }
    last_matched_source = SRC_COUNT;
    return NULL;
}

#endif

// Copyright (c) 2026 Senzdetta