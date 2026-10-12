// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "strings"
    "bufio"
    "path/filepath"
)

func llsiParse(filePath string) ([]string, error) {
    file, err := os.Open(filePath)
    if err != nil {
        return nil, err
    }
    defer file.Close()

    var resolvedPaths []string
    scanner := bufio.NewScanner(file)

    for scanner.Scan() {
        line := strings.TrimSpace(scanner.Text())
        line = strings.ReplaceAll(line, "\r", "")

        if idx := strings.Index(line, "//"); idx != -1 {
            line = strings.TrimSpace(line[:idx])
        }

        if (line == "" ||
            strings.HasPrefix(line, "//") ||
            line == "{" ||
            line == "}") {
                continue
        }

        if strings.Contains(
            line, "{",
        ) && !strings.Contains(line, "->") {
            continue
        }

        if strings.Contains(line, "->") {
            parts := strings.SplitN(line, "->", 2)
            if len(parts) == 2 {
                relPath := strings.TrimSpace(parts[1])
                relPath = strings.Trim(relPath, `"`)
                relPath = strings.Trim(relPath, `'`)

                if relPath != "" {
                    fullPath := filepath.Join(
                        AresRoot, relPath,
                    )

                    resolvedPaths = append(
                        resolvedPaths, fullPath,
                    )
                }
            }
        }
    }

    if err := scanner.Err(); err != nil {
        return nil, err
    }

    return resolvedPaths, nil
}

// Copyright (c) 2026 Senzdetta