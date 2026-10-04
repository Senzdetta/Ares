// https://github.com/Senzdetta/Ares

package main

import (
    "os"
)

func extractTar(src, dest string) error {
    f, err := os.Open(src)
    if err != nil {
        return err
    }
    defer f.Close()

    return extractTarStream(
        f,
        dest,
    )
}

// Copyright (c) 2026 Senzdetta