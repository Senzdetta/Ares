// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
)

func fileExists(path string) bool {
    _, err := os.Stat(path)
    return err == nil
}

// Copyright (c) 2026 Zeronetsec