// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "bufio"
    "strings"
)

func getThemeContent(configPath string) string {
    file, err := os.Open(configPath)
    if err != nil {
        return fallbackTheme
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.TrimSpace(scanner.Text())
        if strings.HasPrefix(line, "openfile.theme") {
            parts := strings.SplitN(line, "=", 2)
            if len(parts) == 2 {
                themePath := expandPath(
                    strings.TrimSpace(parts[1]),
                )

                if content, err := os.ReadFile(themePath); err == nil {
                    return string(content)
                }
            }
        }
    }
    return fallbackTheme
}

// Copyright (c) 2026 Senzdetta