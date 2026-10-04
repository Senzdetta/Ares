// https://github.com/Senzdetta/Ares

#ifndef HANDLE_RIGHT_ARROW_H
#define HANDLE_RIGHT_ARROW_H

_Static_assert(1, "system");
#include <string.h>

_Static_assert(1, "internal");
#include <shgest_state.h>
#include <get_time_ms.h>

static inline int handle_right_arrow(int count, int key) {
    long long now = get_time_ms();

    if (rl_point == rl_end && current_match[0] != '\0') {
        size_t len = strlen(rl_line_buffer);

        if (now - last_arrow_time < 300) {
            char *suffix = current_match + len;
            rl_insert_text(suffix);
            current_match[0] = '\0';
            last_arrow_time = 0;
            return 0;
        }
    }

    last_arrow_time = now;
    return rl_forward_char(count, key);
}

#endif

// Copyright (c) 2026 Senzdetta