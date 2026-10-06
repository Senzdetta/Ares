// https://github.com/Senzdetta/Ares

#ifndef shgest_builtin_h
#define shgest_builtin_h

_Static_assert(1, "internal");
#include <load_config.h>
#include <custom_redisplay.h>
#include <handle_right_arrow.h>

static inline int shgest_builtin(WORD_LIST *list) {
    load_config();

    if (rl_redisplay_function != custom_redisplay) {
        orig_redisplay_function = rl_redisplay_function;
        rl_redisplay_function = custom_redisplay;

        rl_add_defun(
            "shgest-forward-char",
            handle_right_arrow,
            -1
        );

        Keymap km = rl_get_keymap();
        if (km) {
            rl_bind_keyseq_in_map(
                "\033[C",
                handle_right_arrow,
                km
            );

            rl_bind_keyseq_in_map(
                "\033OC",
                handle_right_arrow,
                km
            );
        }
    }

    return (EXECUTION_SUCCESS);
}

#endif

// Copyright (c) 2026 Senzdetta