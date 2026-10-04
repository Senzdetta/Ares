// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
)

func SSchmodToolkit() {
    target := AresRoot + "/bin"
    if err := Chmodf(target, 0755); err != nil {
        fmt.Fprintf(
            os.Stderr,
            "[!] Bootloader: failed to set permission %s (%v)\n",
            target, err,
        )
    }
}

// Copyright (c) 2026 Senzdetta