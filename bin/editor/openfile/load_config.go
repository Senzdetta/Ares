// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "path/filepath"
)

func loadConfig() string {
    customCfg := os.Getenv("__config__")
    return filepath.Join(
        customCfg,
        "openfile.conf",
    )
}

// Copyright (c) 2026 Senzdetta