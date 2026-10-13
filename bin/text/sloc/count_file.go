// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "bufio"
    "strings"
)

func countFile(
    path string,
    rules []CommentRule,
) (FileStats, error) {
    file, err := os.Open(path)
    if err != nil {
        return FileStats{}, err
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    var lines, code, comments, blanks int

    inBlockComment := false
    var activeBlockEnd string

    for scanner.Scan() {
        rawLine := scanner.Text()
        trimmed := strings.TrimSpace(rawLine)

        lines++
        if trimmed == "" {
            blanks++
            continue
        }

        isCommentLine := false
        if inBlockComment {
            comments++
            if strings.Contains(trimmed, activeBlockEnd) {
                inBlockComment = false
            }
            continue
        }

        for _, rule := range rules {
            if rule.IsBlock {
                if strings.HasPrefix(trimmed, rule.BlockStart) {
                    isCommentLine = true
                    comments++
                    if !strings.Contains(
                        trimmed[len(rule.BlockStart):],
                        rule.BlockEnd,
                    ) {
                        inBlockComment = true
                        activeBlockEnd = rule.BlockEnd
                    }
                    break
                }
            } else {
                if rule.Single != "" && strings.HasPrefix(
                    trimmed,
                    rule.Single,
                ) {
                    isCommentLine = true
                    comments++
                    break
                }
            }
        }

        if isCommentLine {
            continue
        }

        code++
    }

    return FileStats{
        Path: path,
        Lines: lines,
        Code: code,
        Comments: comments,
        Blanks: blanks,
    }, nil
}

// Copyright (c) 2026 Senzdetta