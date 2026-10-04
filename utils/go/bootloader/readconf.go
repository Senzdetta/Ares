// https://github.com/Senzdetta/Ares

package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

func Readconf(key string, index int) (string, error) {
    if index < 1 {
        return "", fmt.Errorf(
            "invalid index 0",
        )
    }

    file, err := os.Open(StartupConf)
    if err != nil {
        return "", fmt.Errorf(
            "failed to open %s (%w)",
            StartupConf, err,
        )
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := strings.TrimSpace(scanner.Text())
        line = strings.ReplaceAll(line, "\r", "")

        if line == "" || strings.HasPrefix(line, "#") {
            continue
        }

        parts := strings.SplitN(line, "=", 2)
        if len(parts) < 2 {
            continue
        }

        currentKey := strings.TrimSpace(parts[0])
        if strings.EqualFold(currentKey, key) {
            rawValue := strings.TrimSpace(parts[1])

            rawValue = strings.Trim(rawValue, `"`)
            rawValue = strings.Trim(rawValue, `'`)

            values := strings.Fields(rawValue)

            if index-1 < len(values) {
                cleanVal := strings.TrimSpace(values[index-1])
                cleanVal = strings.ReplaceAll(cleanVal, "\r", "")
                cleanVal = strings.Trim(cleanVal, `"`)
                cleanVal = strings.Trim(cleanVal, `'`)
                return cleanVal, nil
            }

            return "", fmt.Errorf(
                "key %s found, but index %d is out of range (total value: %d)",
                key, index, len(values),
            )
        }
    }

    if err := scanner.Err(); err != nil {
        return "", fmt.Errorf(
            "error read file (%w)",
            err,
        )
    }

    return "", fmt.Errorf(
        "key %s not found in %s",
        key, StartupConf,
    )
}

// Copyright (c) 2026 Senzdetta