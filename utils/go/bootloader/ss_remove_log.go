// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
)

func SSremoveLog() {
    if val, _ := Readconf("remove_log", 1); val == "true" {
        target := Home + "/.ares_log/"
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