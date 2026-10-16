// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "os"
    "path/filepath"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

func cleanupSymlink(targetAlias, binDir string) {
    if targetAlias == "" {
        return
    }

    targetPath := filepath.Join(binDir, targetAlias)
    if _, err := os.Stat(targetPath); err == nil {
        _ = os.Remove(targetPath)
        fmt.Printf(
            "%sUnlink: %s%s%s\n",
            color.N, color.GG, targetPath, color.N,
        )
    }
}

// Copyright (c) 2026 Senzdetta