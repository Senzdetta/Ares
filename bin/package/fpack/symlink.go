// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "os/exec"
    "path/filepath"
)

func symlink(installedName, targetAlias, binDir string) int {
    if installedName == targetAlias {
        return 0
    }

    srcPath, err := exec.LookPath(installedName)
    if err != nil {
        return 1
    }

    targetPath := filepath.Join(binDir, targetAlias)
    if srcPath == targetPath {
        return 0
    }

    _ = os.Remove(targetPath)
    if err := os.Symlink(srcPath, targetPath); err != nil {
        return 1
    }

    return 0
}

// Copyright (c) 2026 Senzdetta