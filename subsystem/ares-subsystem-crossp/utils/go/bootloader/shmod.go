// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "sort"
    "path/filepath"
)

func shmod() error {
    homeDir := os.Getenv("HOME")
    var userShmodDir string
    if homeDir != "" {
        userShmodDir = filepath.Join(
            homeDir, ".ares", "init", "shmod",
        )
    }

    sysShmodDir := filepath.Join(
        AresRoot, "init", "shmod",
    )

    collectValidFiles := func(baseDir string) []string {
        var files []string
        if _, err := os.Stat(baseDir); os.IsNotExist(err) {
            return files
        }

        filepath.Walk(
            baseDir, func(
                path string,
                info os.FileInfo,
                err error,
            ) error {
                if err != nil {
                    return nil
                }

                if !info.IsDir() && hasValidContent(path) {
                    files = append(files, path)
                }

                return nil
            },
        )

        sort.Strings(files)
        return files
    }

    var targetFiles []string
    if userShmodDir != "" {
        userFiles := collectValidFiles(userShmodDir)
        if len(userFiles) > 0 {
            targetFiles = userFiles
        }
    }

    if len(targetFiles) == 0 {
        targetFiles = collectValidFiles(sysShmodDir)
    }

    for _, file := range targetFiles {
        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "source %s",
                file,
            ),
        )
    }

    return nil
}

// Copyright (c) 2026 Senzdetta