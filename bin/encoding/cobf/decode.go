// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "unicode/utf8"
)

func decode(input string, a *Algo, nospace bool) string {
    flen := a.fixedLen
    decodeWord := func(s string) string {
        var sb strings.Builder
        if flen > 0 {
            for len(s) >= flen {
                chunk := s[:flen]
                if r, ok := a.rev[chunk]; ok {
                    sb.WriteRune(r)
                    s = s[flen:]
                } else {
                    r, size := utf8.DecodeRuneInString(s)
                    sb.WriteRune(r)
                    s = s[size:]
                }
            }
        }
        for len(s) > 0 {
            r, size := utf8.DecodeRuneInString(s)
            sb.WriteRune(r)
            s = s[size:]
        }
        return sb.String()
    }

    if nospace {
        return decodeWord(input)
    }

    encodedWords := strings.Split(input, " ")
    decodedWords := make([]string, len(encodedWords))

    for i, w := range encodedWords {
        decodedWords[i] = decodeWord(w)
    }

    return strings.Join(decodedWords, " ")
}

// Copyright (c) 2026 Senzdetta