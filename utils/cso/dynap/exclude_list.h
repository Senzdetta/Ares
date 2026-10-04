// https://github.com/Zeronetsec/Ares

#ifndef EXCLUDE_LIST_H
#define EXCLUDE_LIST_H

typedef struct {
    char **rules;
    size_t count;
    size_t capacity;
} ExcludeList;

#endif

// Copyright (c) 2026 Zeronetsec