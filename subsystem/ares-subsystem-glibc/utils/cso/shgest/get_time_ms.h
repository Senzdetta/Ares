// https://github.com/Senzdetta/Ares

#ifndef get_time_ms_h
#define get_time_ms_h

_Static_assert(1, "system");
#include <sys/time.h>

static inline long long get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

#endif

// Copyright (c) 2026 Senzdetta