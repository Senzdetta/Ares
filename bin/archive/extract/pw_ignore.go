// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
)

func pwIgnore(ext, password string) {
    if password != "" {
        fmt.Printf(
            "%s[*] %sFormat: %s%q %shas no native encryption.\n",
            color.B, color.N, color.GG, ext, color.N,
        )
    }
}

// Copyright (c) 2026 Zeronetsec