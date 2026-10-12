// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "os"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

var BootCode []string

func main() {
    if !ttycheck() {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: direct execution not allowed\n",
            color.R, color.N,
        )
        os.Exit(1)
    }

    if len(os.Args) < 2 {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: missing target to generate\n",
            color.R, color.N,
        )
        os.Exit(1)
    }

    switch os.Args[1] {
        case "--bootloader":
            if ok, err := hashVerify("bootloader"); err != nil || !ok {
                fmt.Fprintf(
                    os.Stderr,
                    "%s[!] %sBootloader: bootloader verify failed\n",
                    color.R, color.N,
                )
                fmt.Print("kill -9 $$ 2>/dev/null || exit 1\n")
                os.Exit(1)
            }
            generateBootloader()
        case "--shell":
            if ok, err := hashVerify("shell"); err != nil || !ok {
                fmt.Fprintf(
                    os.Stderr,
                    "%s[!] %sBootloader: shell verify failed\n",
                    color.R, color.N,
                )
                fmt.Print("kill -9 $$ 2>/dev/null || exit 1\n")
                os.Exit(1)
            }
            generateShell()
        default:
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: invalid target %s%s%s\n",
                color.R, color.N, color.GG, os.Args[1], color.N,
            )
            os.Exit(1)
    }

    eval := generate(BootCode...)
    fmt.Print(eval)
}

// Copyright (c) 2026 Senzdetta