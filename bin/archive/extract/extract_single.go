// https://github.com/Senzdetta/Ares

package main

import (
    "io"
    "os"
    "path/filepath"
)

func extractSingle(
    src, outPath string,
    wrap func(io.Reader) (io.Reader, error),
) error {
    f, err := os.Open(src)
    if err != nil {
        return err
    }
    defer f.Close()

    r, err := wrap(f)
    if err != nil {
        return err
    }

    if err := os.MkdirAll(
        filepath.Dir(outPath),
        0755,
    ); err != nil {
        return err
    }

    out, err := os.Create(outPath)
    if err != nil {
        return err
    }
    defer out.Close()

    _, err = io.Copy(out, r)
    return err
}

// Copyright (c) 2026 Senzdetta