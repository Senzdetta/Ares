// https://github.com/Senzdetta/Ares

package missing_argument

import (
    "fmt"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

func Execute(command string) {
    fmt.Printf(
        "%s[!] %sMissing argument!\n",
        color.R, color.N,
    )

    fmt.Printf(
        "%s[!] %sTry: %saresdoc %s%s%s\n",
        color.R, color.N, color.GG, color.CC, command, color.N,
    )
}

// Copyright (c) 2026 Senzdetta