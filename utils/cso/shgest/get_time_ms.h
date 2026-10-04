// https://github.com/Zeronetsec/Ares

#ifndef GET_TIME_MS_H
#define GET_TIME_MS_H

_Static_assert(1, "system");
#include <sys/time.h>

static inline long long get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

#endif

// Copyright (c) 2026 Zeronetsec