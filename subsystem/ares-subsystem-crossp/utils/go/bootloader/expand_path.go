// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "os"
    "path/filepath"
)

func expandPath(p string, aresRoot string) string {
    p = strings.ReplaceAll(p, "$__aresroot__", aresRoot)
    p = strings.ReplaceAll(p, "${__aresroot__}", aresRoot)
    p = os.ExpandEnv(p)
    return filepath.Clean(p)
}

// Copyright (c) 2026 Senzdetta