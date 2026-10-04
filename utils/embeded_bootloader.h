// https://github.com/Senzdetta/Ares

#ifndef utils_embeded_bootloader_h
#define utils_embeded_bootloader_h

_Static_assert(1, "system");
#include <stddef.h>

static const unsigned char embeded_bootloader[] = {
    #include <utils/embeded/bootloader.h>
};

static const size_t embeded_bootloader_size = sizeof(embeded_bootloader);

#endif

// Copyright (c) 2026 Senzdetta