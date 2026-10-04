// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "os"
    "strings"
    "github.com/Senzdetta/Ares/lib/std/go/color"
    "github.com/Senzdetta/Ares/lib/std/go/missing_argument"
)

func main() {
    args := os.Args[1:]

    var mode, algoPath, outfile, filePath string
    var positional []string

    nospace := false

    for i := 0; i < len(args); i++ {
        switch args[i] {
            case "--mode":
                i++
                if i < len(args) {
                    mode = args[i]
                }
            case "--algo":
                i++
                if i < len(args) {
                    algoPath = args[i]
                }
            case "--outfile":
                i++
                if i < len(args) {
                    outfile = args[i]
                }
            case "--file":
                i++
                if i < len(args) {
                    filePath = args[i]
                }
            case "--nospace":
                nospace = true
            default:
                positional = append(
                    positional,
                    args[i],
                )
        }
    }

    if mode != "encode" && mode != "decode" {
        missing_argument.Execute("cobf")
        os.Exit(1)
    }

    if filePath == "" && len(positional) == 0 {
        missing_argument.Execute("cobf")
        os.Exit(1)
    }

    if algoPath == "" {
        algoPath = os.ExpandEnv(
            "$__config__/cobf_algorithms.cobf",
        )
    }

    algo, err := loadAlgo(algoPath)
    if err != nil {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sFailed to load algorithm: %s%s %s(%s%v%s)%s\n",
            color.R, color.N, color.GG, algoPath, color.DG,
            color.GG, err, color.DG, color.N,
        )
        os.Exit(1)
    }

    var input string
    if filePath != "" {
        b, err := os.ReadFile(filePath)
        if err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sFailed to read file: %s%v%s\n",
                color.R, color.N, color.GG, err, color.N,
            )
            os.Exit(1)
        }
        input = string(b)
    } else {
        input = strings.Join(positional, " ")
    }

    var out string
    if mode == "encode" {
        out = encode(
            input,
            algo,
            nospace,
        )
    } else {
        out = decode(
            input,
            algo,
            nospace,
        )
    }

    if outfile != "" {
        if err := os.WriteFile(
            outfile,
            []byte(out),
            0644,
        ); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sFailed to write output file: %s%v%s\n",
                color.R, color.N, color.GG, err, color.N,
            )
            os.Exit(1)
        }
    } else {
        fmt.Println(out)
    }
}

// Copyright (c) 2026 Senzdetta