// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "path/filepath"
)

func setupEditor(cfgDir string) {
    colorschemesDir := filepath.Join(
        cfgDir,
        "colorschemes",
    )

    themeFile := filepath.Join(
        colorschemesDir,
        "tomorrow-night.micro",
    )

    _ = os.MkdirAll(colorschemesDir, 0755)
    if _, err := os.Stat(themeFile); os.IsNotExist(err) {
        _ = os.WriteFile(
            themeFile,
            []byte(theme),
            0644,
        )
    }
}

// Copyright (c) 2026 Zeronetsec