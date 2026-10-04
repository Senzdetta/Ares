// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
)

func SSremoveBinext() {
    if val, _ := Readconf("remove_binext", 1); val == "true" {
        target := AresRoot + "/bin"
        if err := Rmext(target); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "[!] Bootloader: failed to remove extension %s (%v)\n",
                target, err,
            )
        }
    }
}

// Copyright (c) 2026 Zeronetsec