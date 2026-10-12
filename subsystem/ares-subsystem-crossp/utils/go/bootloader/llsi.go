// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "path/filepath"
)

func llsi() error {
    initPath := filepath.Join(
        AresRoot, "init", "llsi.init",
    )

    modulePaths, err := llsiParse(initPath)
    if err != nil {
        if os.IsNotExist(err) {
            return nil
        }

        return fmt.Errorf(
            "failed to parse llsi.init (%w)",
            err,
        )
    }

    for _, path := range modulePaths {
        if info, err := os.Stat(path); err == nil && !info.IsDir() {
            BootCode = append(
                BootCode,
                fmt.Sprintf(
                    "source %s",
                    path,
                ),
            )
        }
    }

    return nil
}

// Copyright (c) 2026 Senzdetta