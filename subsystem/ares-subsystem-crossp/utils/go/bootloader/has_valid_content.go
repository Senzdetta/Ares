// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "bufio"
    "strings"
)

func hasValidContent(filePath string) bool {
    file, err := os.Open(filePath)
    if err != nil {
        return false
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.TrimSpace(scanner.Text())
        if line != "" && !strings.HasPrefix(line, "#") {
            return true
        }
    }

    return false
}

// Copyright (c) 2026 Senzdetta