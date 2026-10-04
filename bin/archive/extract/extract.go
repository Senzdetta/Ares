// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
    "strings"
    "os"
    "io"
    "path/filepath"
    "compress/bzip2"
    "compress/gzip"
    "github.com/ulikunitz/xz"
    "github.com/klauspost/compress/zstd"
    "github.com/Zeronetsec/Ares/lib/go/color"
    "github.com/Zeronetsec/Ares/lib/go/missing_argument"
    "github.com/Zeronetsec/Ares/lib/go/invalid_option"
)

func main() {
    var (
        destDir string
        customFormat string
        password string
    )

    args := os.Args[1:]
    var positional []string

    for i := 0; i < len(args); i++ {
        arg := args[i]
        if strings.HasPrefix(arg, "-") {
            switch arg {
                case "--format":
                    if i+1 >= len(args) {
                        missing_argument.Execute("extract")
                        os.Exit(1)
                    }
                    customFormat = args[i+1]
                    i++
                case "--password":
                    if i+1 >= len(args) {
                        missing_argument.Execute("extract")
                        os.Exit(1)
                    }
                    password = args[i+1]
                    i++
                default:
                    invalid_option.Execute(
                        strings.Join(args, " "), "extract",
                    )
                    os.Exit(1)
            }
            continue
        }
        positional = append(positional, arg)
    }

    if len(positional) < 1 {
        missing_argument.Execute("extract")
        os.Exit(1)
    }

    fileInput := positional[0]
    if len(positional) > 1 {
        destDir = positional[1]
    }

    customFormat = strings.ToLower(
        strings.TrimPrefix(customFormat, "."),
    )

    if _, err := os.Stat(fileInput); err != nil {
        fmt.Printf(
            "%s[!] %sFile: %s%s %snot found!\n",
            color.R, color.N, color.GG, fileInput, color.N,
        )
        os.Exit(1)
    }

    ext := customFormat
    if ext == "" {
        ext = detectExt(fileInput)
    }

    if destDir != "" {
        if err := os.MkdirAll(
            destDir,
            0755,
        ); err != nil {
            fmt.Printf(
                "%s[!] %sCannot create dest dir: %s%v%s\n",
                color.R, color.N, color.GG, err, color.N,
            )
            os.Exit(1)
        }
    } else {
        destDir = "."
    }

    base := strings.TrimSuffix(
        filepath.Base(fileInput),
        filepath.Ext(fileInput),
    )

    outPath := filepath.Join(destDir, base)

    fmt.Printf(
        "%s[*] %sExtracting: %s%s %s-> %s%s %s(%sFormat: %s%s%s)%s\n",
        color.B, color.N, color.GG, fileInput, color.DG,
        color.GG, destDir, color.DG,
        color.WW, color.CC, ext, color.DG,
        color.N,
    )

    var err error
    switch ext {
        case "zip":
            if password != "" {
                err = extractZipEncrypted(
                    fileInput, destDir, password,
                )
            } else {
                err = extractZip(
                    fileInput, destDir,
                )
            }
        case "tar":
            pwIgnore(ext, password)
            err = extractTar(fileInput, destDir)
        case "tar.gz", "tgz":
            pwIgnore(ext, password)
            err = extractTarGz(fileInput, destDir)
        case "gz", "gzip":
            pwIgnore(ext, password)
            err = extractSingle(
                fileInput, outPath,
                func(r io.Reader) (io.Reader, error) {
                    return gzip.NewReader(r)
                },
            )
        case "tar.bz2", "tbz2", "tbz":
            pwIgnore(ext, password)
            err = extractTarBz2(fileInput, destDir)
        case "bz2", "bzip2", "bzip":
            pwIgnore(ext, password)
            err = extractSingle(
                fileInput, outPath,
                func(r io.Reader) (io.Reader, error) {
                    return bzip2.NewReader(r), nil
                },
            )
        case "tar.xz", "txz":
            pwIgnore(ext, password)
            err = extractTarXz(fileInput, destDir)
        case "xz":
            pwIgnore(ext, password)
            err = extractSingle(
                fileInput, outPath,
                func(r io.Reader) (io.Reader, error) {
                    return xz.NewReader(r)
                },
            )
        case "tar.zst", "tzst":
            pwIgnore(ext, password)
            err = extractTarZst(fileInput, destDir)
        case "zst", "zstd":
            pwIgnore(ext, password)
            err = extractSingle(
                fileInput, outPath,
                func(r io.Reader) (io.Reader, error) {
                    zr, e := zstd.NewReader(r)
                    if e != nil {
                        return nil, e
                    }
                    return zr.IOReadCloser(), nil
                },
            )
        case "7z":
            err = extract7z(
                fileInput, destDir, password,
            )
        case "rar":
            err = extractRar(
                fileInput, destDir, password,
            )
        default:
            fmt.Printf(
                "%s[!] %sFormat: %s%s %sis not supported!\n",
                color.R, color.N, color.GG, ext, color.N,
            )
            os.Exit(1)
    }

    if err != nil {
        fmt.Printf(
            "%s[!] %sExtracting failed: %s%v%s\n",
            color.R, color.N, color.GG, err, color.N,
        )
        os.Exit(1)
    }

    fmt.Printf(
        "%s[+] %sCompleted.\n",
        color.GG, color.N,
    )
}

// Copyright (c) 2026 Zeronetsec