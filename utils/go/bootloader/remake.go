// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "os"
    "strings"
)

func Remake(path string, mode os.FileMode) error {
    isDir := strings.HasSuffix(path, "/")
    if err := os.RemoveAll(path); err != nil && !os.IsNotExist(err) {
        return fmt.Errorf(
            "failed to remove old path %s (%w)",
            path, err,
        )
    }

    if isDir {
        if err := os.MkdirAll(path, mode); err != nil {
            return fmt.Errorf(
                "failed to create %s (%w)",
                path, err,
            )
        }
    } else {
        if idx := strings.LastIndex(path, "/"); idx != -1 {
            parentDir := path[:idx]
            if err := os.MkdirAll(parentDir, 0755); err != nil {
                return fmt.Errorf(
                    "failed to create parent dir %s (%w)",
                    parentDir, err,
                )
            }
        }

        file, err := os.OpenFile(
            path,
            os.O_RDWR|os.O_CREATE|os.O_TRUNC,
            mode,
        )

        if err != nil {
            return fmt.Errorf(
                "failed to create file (%w)",
                err,
            )
        }
        defer file.Close()
    }

    return nil
}

// Copyright (c) 2026 Zeronetsec