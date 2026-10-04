// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "github.com/ulikunitz/xz"
)

func extractTarXz(src, dest string) error {
    f, err := os.Open(src)
    if err != nil {
        return err
    }
    defer f.Close()

    xr, err := xz.NewReader(f)
    if err != nil {
        return err
    }

    return extractTarStream(
        xr,
        dest,
    )
}

// Copyright (c) 2026 Zeronetsec