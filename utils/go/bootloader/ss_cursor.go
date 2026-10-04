// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
)

func SScursor() {
    cursorVal, _ := Readconf("cursor", 1)
    if cursorVal != "native" && cursorVal != "" {
        if err := Setcursor(cursorVal); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "[!] Bootloader: failed to set cursor %s (%v)\n",
                cursorVal, err,
            )
        }
    }
}

// Copyright (c) 2026 Senzdetta