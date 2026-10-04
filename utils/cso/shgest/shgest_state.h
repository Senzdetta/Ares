// https://github.com/Senzdetta/Ares

#ifndef SHGEST_STATE_H
#define SHGEST_STATE_H

_Static_assert(1, "internal");
#include <source_type.h>

extern int rl_terminal_width;

static void (*orig_redisplay_function)(void) = NULL;
static char current_match[1024] = {0};
static long long last_arrow_time = 0;

static SourceType priority_order[SRC_COUNT];
static int priority_enabled[SRC_COUNT] = {0};
static int priority_count = 0;

static char cutter_symbol[32] = "...";
static char cutter_color[64] = "\x1b[1;31m";
static char other_color[64] = "\x1b[38;5;245m";

static char source_colors[SRC_COUNT][64] = {
    "\x1b[1m\x1b[38;2;0;110;185m",
    "\x1b[38;5;245m",
    "\x1b[38;5;202m",
    "\x1b[1m\x1b[38;2;110;90;180m",
    "\x1b[0;34m",
    "\x1b[0;32m",
    "\x1b[0;31m"
};

static SourceType last_matched_source = SRC_COUNT;

#endif

// Copyright (c) 2026 Senzdetta