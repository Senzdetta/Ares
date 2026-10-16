// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "os/exec"
)

func customPkgBackend(cmdPattern, pkg string) int {
    var fullCmd string

    if strings.Contains(cmdPattern, "{}") {
        fullCmd = strings.ReplaceAll(
            cmdPattern, "{}", pkg,
        )
    } else {
        fullCmd = cmdPattern + " " + pkg
    }

    cmd := exec.Command("bash", "-c", fullCmd)
    if err := cmd.Run(); err != nil {
        if exitErr, ok := err.(*exec.ExitError); ok {
            return exitErr.ExitCode()
        }
        return 1
    }

    return 0
}

// Copyright (c) 2026 Senzdetta