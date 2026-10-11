// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "strings"
    "os"
    "bufio"
    "os/exec"
    "path/filepath"
    "github.com/Senzdetta/Ares/lib/std/go/color"
    "github.com/Senzdetta/Ares/lib/std/go/missing_argument"
    "github.com/Senzdetta/Ares/lib/std/go/invalid_option"
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

    var filePath string

    if isRealFile && isAlias {
        fmt.Printf(
            "%s[!] %sConflict found for %s%s%s:\n",
            color.YY, color.N, color.GG, arg, color.N,
        )

        fmt.Printf(
            "  %s› %sfile/directory: %s%s%s\n",
            color.B, color.N, color.GG, arg, color.N,
        )

        fmt.Printf(
            "  %s› %salias: %s%s %s-> %s%s%s\n",
            color.B, color.N, color.GG, arg, color.DG,
            color.GG, resolvePath(arg, configPath), color.N,
        )

        fmt.Printf(
            "%sSelect to open (f/a): ",
            color.N,
        )

        reader := bufio.NewReader(os.Stdin)
        input, _ := reader.ReadString('\n')
        input = strings.TrimSpace(input)

        if input == "a" {
            filePath = resolvePath(arg, configPath)
        } else {
            filePath = expandPath(arg)
        }
    } else if isAlias {
        filePath = resolvePath(arg, configPath)
    } else if isRealFile {
        filePath = expandPath(arg)
    } else {
        filePath = expandPath(arg)
    }

    prefix := os.Getenv("PREFIX")
    if prefix == "" {
        prefix = "/usr"
    }

    rmTemp := filepath.Join(prefix, "tmp", "openfile")
    defer os.RemoveAll(rmTemp)

    microCfgDir := filepath.Join(
        prefix,
        "tmp", "openfile", "theme",
    )

    setupEditor(microCfgDir, configPath)

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

// Copyright (c) 2026 Senzdetta