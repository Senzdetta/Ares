// https://github.com/Zeronetsec/Ares

package main

import (
    "os"
    "fmt"
    "strconv"
    "path/filepath"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
)

func loadConfig() Config {
    cfg := Config{
        RefreshMs: DefaultRefreshMs,
        MaxProcs: DefaultMaxProcs,
    }

    cliConfigPath, cliRefreshMs, cliMaxProcsStr := parseCLIArgs()

    finalConfigPath := cliConfigPath
    if finalConfigPath == "" {
        envConfig := os.Getenv("__config__")
        if envConfig != "" {
            finalConfigPath = filepath.Join(
                envConfig, "atop.conf",
            )
        }
    }

    if finalConfigPath != "" {
        fileCfg, err := parseConfigFile(finalConfigPath)
        if err != nil {
            if cliConfigPath != "" {
                fmt.Fprintf(
                    os.Stderr,
                    "%s[!] %sFailed to read config: %s%s %s(%s%v%s)%s\n",
                    color.R, color.N, color.GG, cliConfigPath, color.DG,
                    color.GG, err, color.DG, color.N,
                )
                os.Exit(1)
            }
        } else {
            if fileCfg.RefreshMs > 0 {
                cfg.RefreshMs = fileCfg.RefreshMs
            }
            if fileCfg.MaxProcs != 0 {
                cfg.MaxProcs = fileCfg.MaxProcs
            }
        }
    }

    if cliRefreshMs > 0 {
        cfg.RefreshMs = cliRefreshMs
    }

    if cliMaxProcsStr != "" {
        if cliMaxProcsStr == "-" {
            cfg.MaxProcs = -1
        } else {
            val, err := strconv.Atoi(cliMaxProcsStr)
            if err != nil {
                fmt.Fprintf(
                    os.Stderr,
                    "%s[!] %sMaxprocess: %s%s %sinvalid value!\n",
                    color.R, color.N, color.GG, cliMaxProcsStr, color.N,
                )
                os.Exit(1)
            }
            cfg.MaxProcs = val
        }
    }
    return cfg
}

// Copyright (c) 2026 Zeronetsec