// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "os"
    "strings"
    "path/filepath"
    "io/fs"
)

func Rmext(target string) error {
    return filepath.WalkDir(
        target, func(
            path string,
            d fs.DirEntry,
            err error,
        ) error {
            if err != nil {
                return err
            }

            if d.IsDir() {
                return nil
            }

            dir := filepath.Dir(path)
            filename := d.Name()

            dotIdx := strings.Index(filename, ".")
            if dotIdx <= 0 {
                return nil
            }

            baseName := filename[:dotIdx]
            newPath := filepath.Join(dir, baseName)
            if newPath == path {
                return nil
            }

            counter := 2
            finalPath := newPath
            for {
                if _, err := os.Stat(finalPath); os.IsNotExist(err) {
                    break
                }
                finalPath = fmt.Sprintf(
                    "%s-%d",
                    newPath, counter,
                )
                counter++
            }

            if err := os.Rename(path, finalPath); err != nil {
                return fmt.Errorf(
                    "failed to rename %s to %s (%w)",
                    path, finalPath, err,
                )
            }

            return nil
        },
    )
}

// Copyright (c) 2026 Senzdetta