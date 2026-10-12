// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "bufio"
    "os"
    "fmt"
    "path/filepath"
)

func dynav() error {
    ignoreMap := make(map[string]bool)
    ignorePath := filepath.Join(
        AresRoot, "config", "dynav_ignore.lst",
    )

    if file, err := os.Open(ignorePath); err == nil {
        defer file.Close()
        scanner := bufio.NewScanner(file)
        for scanner.Scan() {
            line := strings.TrimSpace(scanner.Text())
            if line != "" && !strings.HasPrefix(line, "#") {
                ignoreMap[line] = true
            }
        }
    }

    lockVal, _ := readconf("lock_variable", 1)
    isLocked := strings.EqualFold(lockVal, "true")

    entries, err := os.ReadDir(AresRoot)
    if err != nil {
        return fmt.Errorf(
            "failed to read AresRoot (%w)",
            err,
        )
    }

    for _, entry := range entries {
        if !entry.IsDir() {
            continue
        }

        folderName := entry.Name()
        if ignoreMap[folderName] {
            continue
        }

        dirPath := filepath.Join(AresRoot, folderName)
        varName := fmt.Sprintf(
            "__%s__",
            folderName,
        )

        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "export %s=%s",
                varName, dirPath,
            ),
        )

        if isLocked {
            BootCode = append(
                BootCode,
                fmt.Sprintf(
                    "readonly %s",
                    varName,
                ),
            )
        }
    }

    return nil
}

// Copyright (c) 2026 Senzdetta