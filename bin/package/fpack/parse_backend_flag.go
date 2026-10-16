// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
)

func parseBackendFlag(backendStr string) {
    if strings.TrimSpace(backendStr) == "" {
        return
    }

    pairs := strings.Split(backendStr, ",")
    for _, pair := range pairs {
        pair = strings.TrimSpace(pair)
        if !strings.Contains(pair, "=") {
            continue
        }

        parts := strings.SplitN(pair, "=", 2)
        alias := strings.TrimSpace(parts[0])
        cmdRaw := strings.TrimSpace(parts[1])
        cmdRaw = strings.Trim(cmdRaw, "\"'")

        BackendRegistry[alias] = cmdRaw
    }
}

// Copyright (c) 2026 Senzdetta