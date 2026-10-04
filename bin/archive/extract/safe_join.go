// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
    "strings"
    "path/filepath"
)

func safeJoin(dest, name string) (string, error) {
    fp := filepath.Join(dest, name)
    cleanDest := filepath.Clean(dest) + string(os.PathSeparator)

    if !strings.HasPrefix(
        fp, cleanDest,
    ) && fp != filepath.Clean(dest) {
        return "", fmt.Errorf(
            "illegal file path (zip-slip attempt): %s",
            name,
        )
    }

    return fp, nil
}

// Copyright (c) 2026 Zeronetsec