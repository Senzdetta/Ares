// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "os"
    "path/filepath"
    "io/fs"
)

func Chmodf(target string, mode os.FileMode) error {
    return filepath.WalkDir(
        target, func(
            path string,
            d fs.DirEntry,
            err error,
        ) error {
            if err != nil {
                return err
            }

            if d.IsDir() {
                return nil
            }

            if err := os.Chmod(path, mode); err != nil {
                return fmt.Errorf(
                    "failed to chmod %s (%w)",
                    path, err,
                )
            }

            return nil
        },
    )
}

// Copyright (c) 2026 Zeronetsec