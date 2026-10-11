// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "path/filepath"
)

func setupEditor(cfgDir string, configPath string) {
    colorschemesDir := filepath.Join(cfgDir, "colorschemes")
    themeFile := filepath.Join(
        colorschemesDir,
        "tomorrow-night.micro",
    )

    _ = os.MkdirAll(colorschemesDir, 0755)

    themeContent := getThemeContent(configPath)
    _ = os.WriteFile(
        themeFile,
        []byte(themeContent),
        0644,
    )
}

// Copyright (c) 2026 Senzdetta