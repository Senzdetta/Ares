// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "strings"
    "fmt"
    "github.com/Senzdetta/Ares/lib/std/go/color"
    "github.com/Senzdetta/Ares/lib/std/go/missing_argument"
    "github.com/Senzdetta/Ares/lib/std/go/invalid_option"
)

func main() {
    var configPath string
    var excludeStr string
    var target string

    args := os.Args[1:]
    for i := 0; i < len(args); i++ {
        arg := args[i]
        switch {
            case arg == "--config":
                if i+1 < len(args) {
                    configPath = args[i+1]
                    i++
                } else {
                    missing_argument.Execute("sloc")
                    os.Exit(1)
                }
            case arg == "--exclude":
                if i+1 < len(args) {
                    excludeStr = args[i+1]
                    i++
                } else {
                    missing_argument.Execute("sloc")
                    os.Exit(1)
                }
            case strings.HasPrefix(arg, "-"):
                invalid_option.Execute(arg, "sloc")
                os.Exit(1)
            default:
                if target == "" {
                    target = arg
                } else {
                    fmt.Fprintf(
                        os.Stderr,
                        "%s[!] %sExcess positional argument: %s%s%s\n",
                        color.R, color.N, color.GG, arg, color.N,
                    )
                    os.Exit(1)
                }
        }
    }

    if target == "" {
        missing_argument.Execute("sloc")
        os.Exit(1)
    }

    info, err := os.Stat(target)
    if err != nil {
        if os.IsNotExist(err) {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sDirectory: %s%s %snot found!\n",
                color.R, color.N, color.GG, target, color.N,
            )
        } else {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sError checking directory: %s%v%s\n",
                color.R, color.N, color.GG, err, color.N,
            )
        }
        os.Exit(1)
    }

    if !info.IsDir() {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sTarget: %s%s %sis not directory!\n",
            color.R, color.N, color.GG, target, color.N,
        )
        os.Exit(1)
    }

    rulesMap, err := loadCommentRules(configPath)
    if err != nil {
        fmt.Printf(
            "%s[!] %sError loading config: %s%v%s\n",
            color.R, color.N, color.GG, err, color.N,
        )
        return
    }

    excludeMap := map[string]bool{
        ".git": true,
        ".github": true,
        ".docs": true,
        ".install": true,
        ".devphase": true,
        ".laction": true,
        ".vscode": true,
        "vendor": true,
        "node_modules": true,
    }

    if excludeStr != "" {
        for _, item := range strings.Split(excludeStr, ",") {
            excludeMap[strings.TrimSpace(item)] = true
        }
    }

    runSLOC(target, rulesMap, excludeMap, 8)
}

// Copyright (c) 2026 Senzdetta