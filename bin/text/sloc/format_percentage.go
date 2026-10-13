// https://github.com/Senzdetta/Ares

package main

import (
    "math"
    "fmt"
)

func formatPercentage(p float64) string {
    if p == 0 {
        return "0%"
    }

    if p < 1.0 {
        precision := int(-math.Floor(math.Log10(p))) + 2
        if precision > 6 {
            precision = 6
        }
        return fmt.Sprintf("%.*f%%", precision, p)
    }

    return fmt.Sprintf("%.2f%%", p)
}

// Copyright (c) 2026 Senzdetta