// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "os"
    "os/exec"
)

func extractRarSystem(src, dest, password string) error {
    if _, err := exec.LookPath("unrar"); err != nil {
        return fmt.Errorf(
            "unrar binary not found in $PATH: %w",
            err,
        )
    }

    args := []string{"x", "-o+"}
    if password != "" {
        args = append(args, "-p"+password)
    } else {
        args = append(args, "-p-")
    }

    args = append(
        args, src,
        dest+string(os.PathSeparator),
    )

    cmd := exec.Command("unrar", args...)
    cmd.Stdout = os.Stdout
    cmd.Stderr = os.Stderr

    return cmd.Run()
}

// Copyright (c) 2026 Senzdetta