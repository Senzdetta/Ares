// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
)

func generate(lines ...string) string {
    var builder strings.Builder

    for _, line := range lines {
        builder.WriteString(line)
        builder.WriteString("\n")
    }

    return builder.String()
}

// Copyright (c) 2026 Senzdetta