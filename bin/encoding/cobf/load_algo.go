// https://github.com/Zeronetsec/Ares

package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
    "unicode/utf8"
)

func loadAlgo(path string) (*Algo, error) {
    f, err := os.Open(path)
    if err != nil {
        return nil, err
    }
    defer f.Close()

    a := &Algo{
        fwd: map[rune]string{},
        rev: map[string]rune{},
    }

    seenKey := map[rune]int{}
    seenValue := map[string]int{}

    sc := bufio.NewScanner(f)
    lineNo := 0
    fixedLen := -1

    for sc.Scan() {
        lineNo++
        line := strings.TrimSpace(sc.Text())
        if line == "" || strings.HasPrefix(line, "//") {
            continue
        }

        idx := strings.Index(line, "->")
        if idx == -1 {
            continue
        }

        left := strings.TrimSpace(line[:idx])
        right := strings.TrimSpace(line[idx+2:])
        if left == "" || right == "" {
            continue
        }

        if fixedLen == -1 {
            fixedLen = len(right)
        } else if len(right) != fixedLen {
            return nil, fmt.Errorf(
                "value %q (len: %d) on line %d does not match fixed length (%d), set on line 1",
                right, len(right), lineNo, fixedLen,
            )
        }

        r, _ := utf8.DecodeRuneInString(left)
        if prevLine, exists := seenKey[r]; exists {
            return nil, fmt.Errorf(
                "the key %q on line %d has been defined on line %d",
                string(r), lineNo, prevLine,
            )
        }

        if prevLine, exists := seenValue[right]; exists {
            return nil, fmt.Errorf(
                "value %q on line %d is already used on line %d",
                right, lineNo, prevLine,
            )
        }

        seenKey[r] = lineNo
        seenValue[right] = lineNo

        a.fwd[r] = right
        a.rev[right] = r
    }

    if err := sc.Err(); err != nil {
        return nil, err
    }

    a.fixedLen = fixedLen
    return a, nil
}

// Copyright (c) 2026 Zeronetsec