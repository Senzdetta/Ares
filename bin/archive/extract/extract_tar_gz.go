// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "compress/gzip"
)

func extractTarGz(src, dest string) error {
    f, err := os.Open(src)
    if err != nil {
        return err
    }
    defer f.Close()

    gz, err := gzip.NewReader(f)
    if err != nil {
        return err
    }
    defer gz.Close()

    return extractTarStream(
        gz,
        dest,
    )
}

// Copyright (c) 2026 Zeronetsec