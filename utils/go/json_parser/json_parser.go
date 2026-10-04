// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "os"
    "embed"
    "io/fs"
    "github.com/Zeronetsec/Ares/lib/std/go/color"
)

//go:embed metadata/*.json
var metadataFS embed.FS

func main() {
    files, err := fs.Glob(metadataFS, "metadata/*.json")
    if err != nil {
        fmt.Printf(
            "%s[!] %sFailed to read embedded metadata: %s%v%s\n",
            color.R, color.N, color.GG, err, color.N,
        )
        os.Exit(1)
    }

    if len(files) == 0 {
        fmt.Printf(
            "%s[!] %sNo metadata files found in: %sembed.FS%s\n",
            color.R, color.N, color.GG, color.N,
        )
        return
    }

    for _, filePath := range files {
        processFile(filePath)
    }
}

// Copyright (c) 2026 Zeronetsec