// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
)

func SSremoveGscache() {
    if val, _ := Readconf("remove_gscache", 1); val == "true" {
        target := Prefix + "/tmp/ares/goscript_cache/"
        if err := Remake(target, 0755); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "[!] Bootloader: failed to remove %s (%v)\n",
                target, err,
            )
        }
    }
}

// Copyright (c) 2026 Zeronetsec