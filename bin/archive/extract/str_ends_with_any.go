// https://github.com/Zeronetsec/Ares

package main

import (
    "strings"
)

func strEndsWithAny(s string, suffixes ...string) bool {
    for _, suf := range suffixes {
        if strings.HasSuffix(s, suf) {
            return true
        }
    }
    return false
}

// Copyright (c) 2026 Zeronetsec