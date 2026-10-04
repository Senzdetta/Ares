// https://github.com/Senzdetta/Ares

package main

import (
    "os"
)

func TTYcheck() bool {
    fi, err := os.Stdout.Stat()
    if err != nil {
        return false
    }
    return (fi.Mode() & os.ModeCharDevice) == 0
}

// Copyright (c) 2026 Senzdetta