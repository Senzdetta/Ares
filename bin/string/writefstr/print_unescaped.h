// https://github.com/Senzdetta/Ares

#ifndef print_unescaped_h
#define print_unescaped_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static inline void print_unescaped(int fd, const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '\\' && i + 1 < len) {
            char next = str[i + 1];
            switch (next) {
                case 'n': dprintf(fd, "\n"); i++; continue;
                case 'r': dprintf(fd, "\r"); i++; continue;
                case 't': dprintf(fd, "\t"); i++; continue;
                case 'a': dprintf(fd, "\a"); i++; continue;
                case 'b': dprintf(fd, "\b"); i++; continue;
                case 'f': dprintf(fd, "\f"); i++; continue;
                case 'v': dprintf(fd, "\v"); i++; continue;
                case '\\': dprintf(fd, "\\"); i++; continue;
                case '\"': dprintf(fd, "\""); i++; continue;
                case '\'': dprintf(fd, "\'"); i++; continue;
                case 'x':
                    if (i + 3 < len) {
                        char hex[3] = {str[i+2], str[i+3], '\0'};
                        char val = (char)strtol(hex, NULL, 16);
                        dprintf(fd, "%c", val);
                        i += 3;
                        continue;
                    }
                    break;
            }
        }
        dprintf(fd, "%c", str[i]);
    }
}

#endif

// Copyright (c) 2026 Senzdetta