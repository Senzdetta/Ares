// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "path/filepath"
)

func loadrc() error {
    homeDir := os.Getenv("HOME")
    homeRC := filepath.Join(
        homeDir, ".aresrc",
    )

    defaultRC := filepath.Join(
        AresRoot, "console", "ares.rc",
    )

    targetRC := ""

    if homeDir != "" && hasValidContent(homeRC) {
        targetRC = homeRC
    } else if hasValidContent(defaultRC) {
        targetRC = defaultRC
    }

    if targetRC != "" {
        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "source %s",
                targetRC,
            ),
        )
    }

    return nil
}

// Copyright (c) 2026 Senzdetta