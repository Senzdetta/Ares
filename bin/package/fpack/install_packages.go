// https://github.com/Senzdetta/Ares

package main

import (
    "bufio"
    "os"
)

func installPackages(
    packagesFilePath, defaultBackend, binDir string,
    isUninstall bool,
) error {
    file, err := os.Open(packagesFilePath)
    if err != nil {
        return err
    }
    defer file.Close()

    var lines []string
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        lines = append(lines, scanner.Text())
    }

    if err := scanner.Err(); err != nil {
        return err
    }

    processScriptLines(
        lines, defaultBackend,
        binDir, isUninstall,
    )

    return nil
}

// Copyright (c) 2026 Senzdetta