// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
    "bufio"
    "strings"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
)

func listAlias(configPath string) {
    file, err := os.Open(configPath)
    if err != nil {
        fmt.Printf(
            "%s[!] %sFile: %s%s %snot found!\n",
            color.R, color.N, color.GG, configPath, color.N,
        )
        return
    }
    defer file.Close()

    displayPath := configPath
    if idx := strings.Index(
        configPath, "ares/",
    ); idx != -1 {
        displayPath = configPath[idx:]
    }

    fmt.Printf(
        "%s[*] %sList Aliases %s(%s%s%s)%s:\n",
        color.B, color.N, color.DG,
        color.BB, displayPath, color.DG, color.N,
    )
    hasAlias := false

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
            expandedVal := expandPath(val)

            fmt.Printf(
                "%s› %s%s %s-> %s%s%s\n",
                color.R, color.GG, key, color.DG,
                color.CC, expandedVal, color.N,
            )
            hasAlias = true
        }
    }
    if !hasAlias {
        fmt.Printf(
            "%s› %sempty alias!\n",
            color.R, color.N,
        )
    }
}

// Copyright (c) 2026 Zeronetsec