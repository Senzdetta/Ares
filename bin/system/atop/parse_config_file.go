// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "bufio"
    "strings"
    "strconv"
)

func parseConfigFile(path string) (Config, error) {
    var cfg Config

    file, err := os.Open(path)
    if err != nil {
        return cfg, err
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.TrimSpace(scanner.Text())

        if line == "" || strings.HasPrefix(line, "#") {
            continue
        }

        parts := strings.SplitN(line, "=", 2)
        if len(parts) != 2 {
            continue
        }

        key := strings.ToLower(
            strings.TrimSpace(parts[0]),
        )
        valStr := strings.TrimSpace(parts[1])

        switch key {
            case "refreshms":
                if val, err := strconv.Atoi(
                    valStr,
                ); err == nil {
                    cfg.RefreshMs = val
                }
            case "maxprocess":
                if valStr == "-" {
                    cfg.MaxProcs = -1
                } else if val, err := strconv.Atoi(
                    valStr,
                ); err == nil {
                    cfg.MaxProcs = val
                }
        }
    }

    return cfg, scanner.Err()
}

// Copyright (c) 2026 Zeronetsec