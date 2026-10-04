// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "compress/bzip2"
)

func extractTarBz2(src, dest string) error {
    f, err := os.Open(src)
    if err != nil {
        return err
    }
    defer f.Close()

    return extractTarStream(
        bzip2.NewReader(f),
        dest,
    )
}

// Copyright (c) 2026 Zeronetsec