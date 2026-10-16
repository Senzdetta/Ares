// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "fmt"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

func processScriptLines(
    lines []string,
    defaultBackend, binDir string,
    isUninstall bool,
) {
    var packageLines []string
    for _, line := range lines {
        line = strings.TrimSpace(line)
        if line == "" || strings.HasPrefix(
            line, "#",
        ) || strings.HasPrefix(line, "//") {
            continue
        }

        if strings.Contains(line, "=") {
            parts := strings.SplitN(line, "=", 2)
            alias := strings.TrimSpace(parts[0])
            cmdRaw := strings.TrimSpace(parts[1])
            cmdRaw = strings.Trim(cmdRaw, "\"'")

            BackendRegistry[alias] = cmdRaw
            continue
        }

        packageLines = append(packageLines, line)
    }

    actionStr := "Installing"
    if isUninstall {
        actionStr = "Uninstalling"
    }

    for _, line := range packageLines {
        fmt.Printf(
            "%s[*] %s%s: %s%s%s\n",
            color.B, color.N, actionStr, color.GG, line, color.N,
        )

        parser(
            line, defaultBackend,
            binDir, isUninstall,
        )
    }
}

// Copyright (c) 2026 Senzdetta