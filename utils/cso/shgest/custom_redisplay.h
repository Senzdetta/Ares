// https://github.com/Senzdetta/Ares

#ifndef custom_redisplay_h
#define custom_redisplay_h

_Static_assert(1, "system");
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <shgest_state.h>
#include <find_match.h>
#include <get_visible_width.h>
#include <print_colored_suffix.h>

static inline void custom_redisplay(void) {
    if (orig_redisplay_function) {
        orig_redisplay_function();
    }

    if (
        !rl_line_buffer ||
        rl_line_buffer[0] == '\0' ||
        rl_point < rl_end
    ) {
        current_match[0] = '\0';
        int move_right = rl_end - rl_point;
        if (move_right > 0) {
            printf(
                "\x1b[%dC",
                move_right
            );
        }

        printf("\x1b[K");

        if (move_right > 0) {
            printf(
                "\x1b[%dD",
                move_right
            );
        }

        fflush(stdout);
        return;
    }

    size_t len = strlen(rl_line_buffer);
    char *match = find_match(
        rl_line_buffer,
        len
    );

    if (match) {
        snprintf(
            current_match,
            sizeof(current_match),
            "%s",
            match
        );
        char *suffix = match + len;

        int cols = 80;
        struct winsize w;
        if (
            ioctl(
                STDOUT_FILENO, TIOCGWINSZ, &w
            ) == 0 &&
            w.ws_col > 0
        ) {
            cols = w.ws_col;
        } else {
            char *cols_env = getenv("COLUMNS");
            if (cols_env) {
                cols = atoi(cols_env);
            }
        }

        int prompt_len = 0;
        if (rl_prompt) {
            const char *last_newline = strrchr(
                rl_prompt,
                '\n'
            );
            if (last_newline) {
                prompt_len = get_visible_width(
                    last_newline + 1
                );
            } else {
                prompt_len = get_visible_width(rl_prompt);
            }
        }

        char current_input[1024] = {0};
        int print_input_len = (rl_point < 1023) ?
            rl_point :
            1023;

        strncpy(
            current_input,
            rl_line_buffer,
            print_input_len
        );

        int input_len = get_visible_width(current_input);
        int total_visual_len = prompt_len + input_len;

        int current_col = total_visual_len % cols;
        int available_space = cols - current_col - 1;

        if (available_space <= 0) {
            free(match);
            return;
        }

        size_t suffix_len = strlen(suffix);

        printf("\x1b[K");

        int cutter_len = get_visible_width(cutter_symbol);
        if (cutter_len <= 0) {
            cutter_len = 3;
        }

        if (
            available_space > cutter_len &&
            (int)suffix_len > available_space
        ) {
            char truncated[1024] = {0};
            int print_len = available_space - cutter_len;

            strncpy(
                truncated,
                suffix,
                print_len
            );
            truncated[print_len] = '\0';

            print_colored_suffix(truncated);
            printf(
                "%s%s%s",
                cutter_color[0] ? cutter_color : color_R,
                cutter_symbol[0] ? cutter_symbol : "...",
                color_N
            );

            printf(
                "\x1b[%dD",
                print_len + cutter_len
            );
        } else if (
            (int)suffix_len <= available_space
        ) {
            print_colored_suffix(suffix);
            printf(
                "\x1b[%dD",
                (int)suffix_len
            );
        }

        fflush(stdout);
        free(match);
    } else {
        current_match[0] = '\0';
        printf("\x1b[K");
        fflush(stdout);
    }
}

#endif

// Copyright (c) 2026 Senzdetta