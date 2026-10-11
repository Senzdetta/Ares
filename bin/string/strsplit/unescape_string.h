// https://github.com/Senzdetta/Ares

#ifndef unescape_string_h
#define unescape_string_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char* unescape_string(const char *src) {
    if (!src) {
        return NULL;
    }

    size_t len = strlen(src);
    char *dest = malloc(len + 1);
    if (!dest) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (src[i] == '\\' && i + 1 < len) {
            i++;
            switch (src[i]) {
                case 'n': dest[j++] = '\n'; break;
                case 't': dest[j++] = '\t'; break;
                case 'r': dest[j++] = '\r'; break;
                case '0': dest[j++] = '\0'; break;
                case 'x': {
                    if (i + 2 < len) {
                        char hex[3] = {src[i+1], src[i+2], '\0'};
                        dest[j++] = (char)strtol(hex, NULL, 16);
                        i += 2;
                    } else {
                        dest[j++] = '\\';
                        dest[j++] = 'x';
                    }
                    break;
                }
                default:
                    dest[j++] = '\\';
                    dest[j++] = src[i];
                    break;
            }
        } else {
            dest[j++] = src[i];
        }
    }
    dest[j] = '\0';
    return dest;
}

#endif

// Copyright (c) 2026 Senzdetta