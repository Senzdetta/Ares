// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
)

func BSgen() {
    info, err := os.Stat(BootloaderFile)
    if err != nil || info.IsDir() {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: missing %s%s%s\n",
            color.R, color.N, color.GG, BootloaderFile, color.N,
        )
        os.Exit(1)
    }

    loadso := AresRoot + "/utils/cso/loadso.so"
    info, err = os.Stat(loadso)
    if err != nil || info.IsDir() {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: missing %s%s%s\n",
            color.R, color.N, color.GG, loadso, color.N,
        )
        os.Exit(1)
    }

    if val, _ := Readconf("lock_variable", 1); val == "true" {
        BootCode = append(
            BootCode,
            `
                readonly __aresroot__
                readonly __areslog__
                readonly __aresrc__
                readonly __shmoduser__
            `,
        )
    }

    BootCode = append(
        BootCode,
        fmt.Sprintf(
            `
                enable -f %s loadso
                source %s
            `,
            loadso, BootloaderFile,
        ),
    )
}

// Copyright (c) 2026 Zeronetsec