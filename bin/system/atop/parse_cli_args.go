// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
    "strconv"
    "strings"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
    "github.com/Zeronetsec/Ares/lib/std/go/missing_argument"
    "github.com/Zeronetsec/Ares/lib/std/go/invalid_option"
)

func parseCLIArgs() (
    configPath string,
    refreshMs int,
    maxProcsStr string,
) {
    args := os.Args[1:]
    for i := 0; i < len(args); i++ {
        arg := args[i]
        if arg == "--config" {
            if i+1 >= len(args) {
                missing_argument.Execute("atop")
                os.Exit(1)
            }
            configPath = args[i+1]
            i++
            continue
        }

        if arg == "--refreshms" {
            if i+1 >= len(args) {
                missing_argument.Execute("atop")
                os.Exit(1)
            }
            val, err := strconv.Atoi(args[i+1])
            if err != nil || val <= 0 {
                fmt.Fprintf(
                    os.Stderr,
                    "%s[!] %sRefreshms: %s%s %sinvalid value!\n",
                    color.R, color.N, color.GG, args[i+1], color.N,
                )
                os.Exit(1)
            }
            refreshMs = val
            i++
            continue
        }

        if arg == "--maxprocess" {
            if i+1 >= len(args) {
                missing_argument.Execute("atop")
                os.Exit(1)
            }
            maxProcsStr = args[i+1]
            i++
            continue
        }

        if strings.HasPrefix(arg, "-") {
            invalid_option.Execute(arg, "atop")
            os.Exit(1)
        }
    }

    return configPath, refreshMs, maxProcsStr
}

// Copyright (c) 2026 Zeronetsec