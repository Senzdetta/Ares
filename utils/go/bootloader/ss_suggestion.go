// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
)

func SSsuggestion() {
    if val, _ := Readconf("suggestion", 1); val == "true" {
        if val, _ := Readconf("suggestion", 2); val != "--force" {
            BootCode = append(
                BootCode,
                `
                    command acon \
                        "${__aresroot__}/data/startup_notify/suggestion.acon"
                `,
            )
        }

        suggestionEngine, _ := Readconf("suggestion_engine", 1)
        if suggestionEngine == "shgest" {
            BootCode = append(
                BootCode,
                `
                    builtin loadso : '(
                        utils/cso/shgest -> shgest
                    )'
                `,
            )
        }

        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "source \"${__aresroot__}/init/engine/suggestion/%s.shx\" || true\n",
                suggestionEngine,
            ),
        )
    }
}

// Copyright (c) 2026 Zeronetsec