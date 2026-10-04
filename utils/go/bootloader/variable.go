// https://github.com/Senzdetta/Ares

package main

import (
    "embed"
    "os"
    "strings"
    "path/filepath"
)

//go:embed hash
var hashFS embed.FS

var (
    Prefix string
    Home string
    AresRoot string
    StartupConf string
    ShellFile string
    BootloaderFile string
    ShellHash string
    BootloaderHash string
)

func init() {
    Prefix = os.Getenv("PREFIX")
    if Prefix == "" {
        Prefix = "/usr"
    }

    Home = os.Getenv("HOME")

    AresRoot = os.Getenv("__aresroot__")
    StartupConf = filepath.Join(
        AresRoot,
        "config", "startup.conf",
    )

    ShellFile = filepath.Join(
        AresRoot,
        "console", "shell.sh",
    )

    BootloaderFile = filepath.Join(
        AresRoot,
        "init", "bootloader.sh",
    )

    shellBytes, _ := hashFS.ReadFile(
        "hash/shell.hash",
    )

    bootloaderBytes, _ := hashFS.ReadFile(
        "hash/bootloader.hash",
    )

    ShellHash = strings.TrimSpace(string(shellBytes))
    BootloaderHash = strings.TrimSpace(string(bootloaderBytes))
}

// Copyright (c) 2026 Senzdetta