// https://github.com/Zeronetsec/Ares

package main

import (
    "strings"
)

func Generate(lines ...string) string {
    var builder strings.Builder

    for _, line := range lines {
        builder.WriteString(line)
    }

    return builder.String()
}

// Copyright (c) 2026 Zeronetsec