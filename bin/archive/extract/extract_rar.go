// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
)

func extractRar(src, dest, password string) error {
    if err := extractRarNative(
        src, dest, password,
    ); err != nil {
        fmt.Printf(
            "%s[!] %sRardecode failed: %s%w%s\n",
            color.R, color.N, color.GG, err, color.N,
        )

        fmt.Printf(
            "%s[*] %sFalling back to unrar binary...\n",
            color.B, color.N,
        )

        return extractRarSystem(
            src, dest, password,
        )
    }

    return nil
}

// Copyright (c) 2026 Zeronetsec