// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_h
#define utils_crawlpath_h

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <utils/crawlpath/crawler.h>

static inline void crawlpath(void) {
    crawler();
}

#endif

// Copyright (c) 2026 Senzdetta