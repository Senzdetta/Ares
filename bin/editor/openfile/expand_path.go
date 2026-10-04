// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "strings"
    "path/filepath"
)

func expandPath(path string) string {
    path = os.ExpandEnv(path)

    if strings.HasPrefix(path, "~/") {
        home, err := os.UserHomeDir()
        if err == nil {
            return filepath.Join(home, path[2:])
        }
    } else if path == "~" {
        home, err := os.UserHomeDir()
        if err == nil {
            return home
        }
    }

    return path
}

// Copyright (c) 2026 Zeronetsec