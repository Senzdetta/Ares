// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "bufio"
    "strings"
)

func isAliasExist(aliasName string, configPath string) bool {
    file, err := os.Open(configPath)
    if err != nil {
        return false
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.TrimSpace(scanner.Text())

        if line == "" || strings.HasPrefix(line, "#") {
            continue
        }

        parts := strings.SplitN(line, "=", 2)
        if len(parts) == 2 {
            key := strings.TrimSpace(parts[0])
            if key == aliasName {
                return true
            }
        }
    }

    return false
}

// Copyright (c) 2026 Zeronetsec