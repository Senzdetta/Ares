// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "bufio"
    "strings"
    "path/filepath"
)

func dynap() error {
    excludeMap := make(map[string]bool)
    excludePath := filepath.Join(
        AresRoot, "config", "dynap_exclude.lst",
    )

    if file, err := os.Open(excludePath); err == nil {
        defer file.Close()
        scanner := bufio.NewScanner(file)
        for scanner.Scan() {
            line := strings.TrimSpace(scanner.Text())
            if line != "" && !strings.HasPrefix(line, "#") {
                excludeMap[expandPath(line, AresRoot)] = true
            }
        }
    }

    var toolkitLine string
    if file, err := os.Open(StartupConf); err == nil {
        defer file.Close()
        scanner := bufio.NewScanner(file)
        for scanner.Scan() {
            line := strings.TrimSpace(scanner.Text())
            line = strings.ReplaceAll(line, "\r", "")
            if line == "" || strings.HasPrefix(line, "#") {
                continue
            }

            parts := strings.SplitN(line, "=", 2)
            if len(parts) == 2 && strings.EqualFold(
                strings.TrimSpace(parts[0]), "toolkit",
            ) {
                toolkitLine = strings.TrimSpace(parts[1])
                break
            }
        }
    }

    isReadonly := false
    var rawPaths []string

    if toolkitLine != "" {
        parts := strings.Split(toolkitLine, ",")
        for _, p := range parts {
            p = strings.TrimSpace(p)
            p = strings.Trim(p, `"`)
            p = strings.Trim(p, `'`)

            if p == "" {
                continue
            }

            if p == "<+readonly>" {
                isReadonly = true
                continue
            }

            if p == "<-readonly>" {
                isReadonly = false
                continue
            }

            rawPaths = append(rawPaths, p)
        }
    }

    var finalPaths []string
    seen := make(map[string]bool)

    addPathPath := func(p string) {
        cleanP := filepath.Clean(p)
        if excludeMap[cleanP] {
            return
        }

        if !seen[cleanP] {
            seen[cleanP] = true
            finalPaths = append(finalPaths, cleanP)
        }
    }

    for _, rp := range rawPaths {
        expanded := expandPath(rp, AresRoot)
        if info, err := os.Stat(expanded); err == nil && info.IsDir() {
            filepath.Walk(
                expanded, func(
                    path string,
                    info os.FileInfo,
                    err error,
                ) error {
                    if err != nil {
                        return nil
                    }

                    if info.IsDir() {
                        addPathPath(path)
                    }

                    return nil
                },
            )
        }
    }

    osPath := os.Getenv("PATH")
    if osPath != "" {
        osParts := strings.Split(
            osPath,
            string(os.PathListSeparator),
        )

        for _, op := range osParts {
            op = strings.TrimSpace(op)
            if op != "" {
                addPathPath(op)
            }
        }
    }

    if len(finalPaths) > 0 {
        pathStr := strings.Join(finalPaths, ":")
        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "export PATH=%s",
                pathStr,
            ),
        )

        if isReadonly {
            BootCode = append(
                BootCode,
                "readonly PATH",
            )
        }
    }

    return nil
}

// Copyright (c) 2026 Senzdetta