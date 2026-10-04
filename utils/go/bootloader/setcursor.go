// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
)

func Setcursor(style string) error {
    switch style {
        case "default":
            fmt.Print(
                "printf '\x1b[0 q'\n",
            )
        case "blink-block":
            fmt.Print(
                "printf '\x1b[1 q'\n",
            )
        case "block":
            fmt.Print(
                "printf '\x1b[2 q'\n",
            )
        case "blink-underline":
            fmt.Print(
                "printf '\x1b[3 q'\n",
            )
        case "underline":
            fmt.Print(
                "printf '\x1b[4 q'\n",
            )
        case "blink-line":
            fmt.Print(
                "printf '\x1b[5 q'\n",
            )
        case "line":
            fmt.Print(
                "printf '\x1b[6 q'\n",
            )
        default:
            return fmt.Errorf(
                "invalid cursor style %s",
                style,
            )
    }
    return nil
}

// Copyright (c) 2026 Zeronetsec