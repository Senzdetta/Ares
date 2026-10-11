// https://github.com/Senzdetta/Ares

#ifndef utils_crawlpath_exclude_list_h
#define utils_crawlpath_exclude_list_h

#define MAX_EXCLUDES 256
#define MAX_PATH_LEN 4096
#define PATH_BUF_SIZE 65536

typedef struct {
    char paths[MAX_EXCLUDES][MAX_PATH_LEN];
    int count;
} ExcludeList;

#endif

// Copyright (c) 2026 Senzdetta