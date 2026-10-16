// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
)

func splitInstallString(input string) []string {
    var results []string
    var current strings.Builder

    depth := 0

    for _, r := range input {
        if r == '(' {
            depth++
        } else if r == ')' {
            depth--
        }

        if r == ',' && depth == 0 {
            results = append(results, current.String())
            current.Reset()
        } else {
            current.WriteRune(r)
        }
    }

    if current.Len() > 0 {
        results = append(results, current.String())
    }

    return results
}

// Copyright (c) 2026 Senzdetta