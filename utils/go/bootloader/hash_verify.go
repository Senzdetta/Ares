// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "io"
    "os"
    "strings"
    "crypto/sha256"
    "encoding/hex"
)

func HashVerify(targetType string) (bool, error) {
    var targetFilePath string
    var expectedHash string

    switch strings.ToLower(targetType) {
        case "shell":
            targetFilePath = ShellFile
            expectedHash = ShellHash
        case "bootloader":
            targetFilePath = BootloaderFile
            expectedHash = BootloaderHash
        default:
            return false, fmt.Errorf(
                "invalid target type %s",
                targetType,
            )
    }

    file, err := os.Open(targetFilePath)
    if err != nil {
        return false, fmt.Errorf(
            "failed to open %s (%w)",
            targetFilePath, err,
        )
    }
    defer file.Close()

    hasher := sha256.New()
    if _, err := io.Copy(hasher, file); err != nil {
        return false, fmt.Errorf(
            "failed to calculate hash (%w)",
            err,
        )
    }

    calculatedHash := hex.EncodeToString(
        hasher.Sum(nil),
    )

    return strings.EqualFold(
        calculatedHash,
        expectedHash,
    ), nil
}

// Copyright (c) 2026 Zeronetsec