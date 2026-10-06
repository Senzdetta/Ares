// https://github.com/Senzdetta/Ares

#ifndef options_h
#define options_h

_Static_assert(1, "system");
#include <stdbool.h>
#include <sys/stat.h>

typedef struct {
    mode_t mode_dir;
    mode_t mode_file;
    mode_t mode_symlink;

    bool mode_dir_set;
    bool mode_file_set;
    bool mode_symlink_set;

    bool only_file;
    bool only_dir;
    bool only_symlink;
    
    bool recursive;
    char ext[256];
    bool has_ext;
} Options;

#endif

// Copyright (c) 2026 Senzdetta