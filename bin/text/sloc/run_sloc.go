// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "time"
    "sync"
    "strings"
    "fmt"
    "sort"
    "path/filepath"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

func runSLOC(
    root string,
    rulesMap map[string][]LangBinding,
    excludeMap map[string]bool,
    numWorkers int,
) {
    start := time.Now()

    filesChan := make(chan string, 1000)
    resultsChan := make(chan FileStats, 1000)

    var wg sync.WaitGroup
    parentDir := filepath.Dir(filepath.Clean(root))

    for i := 0; i < numWorkers; i++ {
        wg.Add(1)
        go func() {
            defer wg.Done()
            for path := range filesChan {
                ext := strings.ToLower(
                    filepath.Ext(path),
                )

                relPath, err := filepath.Rel(parentDir, path)
                if err != nil {
                    relPath = path
                }

                if ext == "" {
                    resultsChan <- FileStats{
                        Path: relPath,
                        FileType: "no_ext",
                    }
                    continue
                }

                bindings, exists := rulesMap[ext]
                if !exists {
                    resultsChan <- FileStats{
                        Path: relPath,
                        Ext: ext,
                        FileType: "unknown",
                    }
                    continue
                }

                for _, binding := range bindings {
                    stats, err := countFile(path, binding.Rules)
                    if err == nil {
                        stats.Path = relPath
                        stats.Ext = ext
                        stats.LangName = binding.LangName
                        stats.FileType = "code"
                        resultsChan <- stats
                    }
                }
            }
        }()
    }

    go func() {
        wg.Wait()
        close(resultsChan)
    }()

    go func() {
        filepath.WalkDir(
            root, func(
                path string,
                d os.DirEntry,
                err error,
            ) error {
                if err != nil {
                    return nil
                }

                name := d.Name()
                if (excludeMap[name] ||
                    (d.IsDir() && strings.HasPrefix(
                        name, ".",
                    ))) {
                        if d.IsDir() {
                            return filepath.SkipDir
                        }

                        return nil
                }

                if !d.IsDir() {
                    filesChan <- path
                }

                return nil
            },
        )
        close(filesChan)
    }()

    var totalLines, totalCode, totalComments, totalBlanks int

    uniqueCodeFiles := make(map[string]bool)
    langStatsMap := make(map[string]*LangStat)

    var unknownFiles []string
    var noExtFiles []string

    for res := range resultsChan {
        switch res.FileType {
            case "no_ext":
                noExtFiles = append(
                    noExtFiles,
                    res.Path,
                )
            case "unknown":
                unknownFiles = append(
                    unknownFiles,
                    fmt.Sprintf(
                        "%s = %s",
                        res.Path, res.Ext,
                    ),
                )
            case "code":
                uniqueCodeFiles[res.Path] = true
                totalLines += res.Lines
                totalCode += res.Code
                totalComments += res.Comments
                totalBlanks += res.Blanks

                if _, ok := langStatsMap[res.LangName]; !ok {
                    langStatsMap[res.LangName] = &LangStat{
                        Name: res.LangName,
                    }
                }

                langStatsMap[res.LangName].FileCount++
                langStatsMap[res.LangName].TotalCode += res.Code
        }
    }

    duration := time.Since(start)
    dirName := filepath.Base(root)

    if root == "." {
        if cwd, err := os.Getwd(); err == nil {
            dirName = filepath.Base(cwd)
        }
    }

    fmt.Printf(
        "%sDirectory: %s%s%s\n",
        color.N, color.GG, dirName, color.N,
    )

    fmt.Printf(
        "%sScanned files: %s%d%s\n",
        color.N, color.GG, len(uniqueCodeFiles), color.N,
    )

    fmt.Printf(
        "%sTotal lines: %s%d%s\n",
        color.N, color.GG, totalLines, color.N,
    )

    fmt.Printf(
        "%sCode lines: %s%d%s\n",
        color.N, color.GG, totalCode, color.N,
    )

    fmt.Printf(
        "%sComment lines: %s%d%s\n",
        color.N, color.GG, totalComments, color.N,
    )

    fmt.Printf(
        "%sBlank lines: %s%d%s\n",
        color.N, color.GG, totalBlanks, color.N,
    )

    fmt.Printf(
        "%sExecution time: %s%v%s\n",
        color.N, color.GG, duration, color.N,
    )

    fmt.Printf("\n")
    fmt.Printf(
        "%sMost used file types:\n",
        color.N,
    )

    if totalCode > 0 {
        var sortedLangs []*LangStat
        for _, stat := range langStatsMap {
            sortedLangs = append(sortedLangs, stat)
        }

        sort.Slice(
            sortedLangs, func(
                i, j int,
            ) bool {
                return sortedLangs[i].TotalCode > sortedLangs[j].TotalCode
            },
        )

        for _, stat := range sortedLangs {
            percentage := (float64(stat.TotalCode) / float64(totalCode)) * 100
            fmt.Printf(
                "%s› %s%s %s(%s%s%s)%s\n",
                color.R, color.GG, stat.Name,
                color.DG, color.CC, formatPercentage(percentage), color.DG,
                color.N,
            )

            fmt.Printf(
                "  %s├── %stotal files: %s%d%s\n",
                color.DG, color.WW, color.GG, stat.FileCount, color.N,
            )

            fmt.Printf(
                "  %s└── %stotal lines: %s%d%s\n",
                color.DG, color.WW, color.GG, stat.TotalCode, color.N,
            )
        }
    } else {
        fmt.Printf(
            "%s[!] %sNo lines of code detected!\n",
            color.R, color.N,
        )
    }

    if len(unknownFiles) > 0 {
        fmt.Printf("\n")
        fmt.Printf(
            "%sUnknown files:\n",
            color.N,
        )

        uidx := 0
        for _, uf := range unknownFiles {
            uidx++
            fmt.Printf(
                "%s› %s%d. %s%s%s\n",
                color.R, color.WW, uidx, color.GG, uf, color.N,
            )
        }

        fmt.Printf(
            "%sTotal unknown files: %s%d%s\n",
            color.N, color.GG, uidx, color.N,
        )
    }

    if len(noExtFiles) > 0 {
        fmt.Printf("\n")
        fmt.Printf(
            "%sNo extension files:\n",
            color.N,
        )

        nidx := 0
        for _, nef := range noExtFiles {
            nidx++
            fmt.Printf(
                "%s› %s%d. %s%s%s\n",
                color.R, color.WW, nidx, color.GG, nef, color.N,
            )
        }

        fmt.Printf(
            "%sTotal no extension files: %s%d%s\n",
            color.N, color.GG, nidx, color.N,
        )
    }
}

// Copyright (c) 2026 Senzdetta