// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "strings"
    "os"
    "os/exec"
    "path/filepath"
    "github.com/Zeronetsec/Ares/lib/go/color"
    "github.com/Zeronetsec/Ares/lib/go/missing_argument"
    "github.com/Zeronetsec/Ares/lib/go/invalid_option"
)

func main() {
    if len(os.Args) < 2 {
        missing_argument.Execute("openfile")
        os.Exit(1)
    }

    arg := os.Args[1]
    configPath := loadConfig()

    if arg == "--list-alias" {
        listAlias(configPath)
        return
    }

    isRealFile := fileExists(arg)
    isAlias := isAliasExist(arg, configPath)

    if !isRealFile && !isAlias && strings.HasPrefix(arg, "-") {
        invalid_option.Execute(arg, "openfile")
        os.Exit(1)
    }

    prefix := os.Getenv("PREFIX")
    if prefix == "" {
        prefix = "/usr"
    }

    rmTemp := filepath.Join(
        prefix, "tmp", "openfile",
    )
    defer os.RemoveAll(rmTemp)

    microCfgDir := filepath.Join(
        prefix,
        "tmp",
        "openfile",
        "theme",
    )
    setupEditor(microCfgDir)

    filePath := resolvePath(arg, configPath)
    cmd := exec.Command("micro",
        "-config-dir",
        microCfgDir,
        "-colorscheme",
        "tomorrow-night",
        filePath,
    )

    cmd.Stdin = os.Stdin
    cmd.Stdout = os.Stdout
    cmd.Stderr = os.Stderr

    if err := cmd.Run(); err != nil {
        fmt.Printf(
            "%s[!] %sFailed to execute micro: %s%v%s\n",
            color.R, color.N, color.GG, err, color.N,
        )
        return
    }
}

// Copyright (c) 2026 Zeronetsec