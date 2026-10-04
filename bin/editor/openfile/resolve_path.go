// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "bufio"
    "strings"
)

func resolvePath(target string, configPath string) string {
    file, err := os.Open(configPath)
    if err != nil {
        return expandPath(target)
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
            val := strings.TrimSpace(parts[1])
            if key == target {
                return expandPath(val)
            }
        }
    }

    return expandPath(target)
}

// Copyright (c) 2026 Senzdetta