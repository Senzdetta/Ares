// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
)

func encode(input string, a *Algo, nospace bool) string {
    if nospace {
        input = strings.ReplaceAll(input, " ", "")
        var sb strings.Builder
        for _, r := range input {
            if v, ok := a.fwd[r]; ok {
                sb.WriteString(v)
            } else {
                sb.WriteRune(r)
            }
        }
        return sb.String()
    }

    words := strings.Split(input, " ")
    encodedWords := make([]string, len(words))

    for i, word := range words {
        var sb strings.Builder
        for _, r := range word {
            if v, ok := a.fwd[r]; ok {
                sb.WriteString(v)
            } else {
                sb.WriteRune(r)
            }
        }
        encodedWords[i] = sb.String()
    }

    return strings.Join(encodedWords, " ")
}

// Copyright (c) 2026 Senzdetta