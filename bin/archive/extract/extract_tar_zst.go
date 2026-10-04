// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "github.com/klauspost/compress/zstd"
)

func extractTarZst(src, dest string) error {
    f, err := os.Open(src)
    if err != nil {
        return err
    }
    defer f.Close()

    zr, err := zstd.NewReader(f)
    if err != nil {
        return err
    }
    defer zr.Close()

    return extractTarStream(
        zr.IOReadCloser(),
        dest,
    )
}

// Copyright (c) 2026 Zeronetsec