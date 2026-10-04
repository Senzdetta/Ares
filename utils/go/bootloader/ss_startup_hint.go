// https://github.com/Zeronetsec/Ares

package main

func SSstartupHint() {
    if val, _ := Readconf("startup_hint", 1); val == "true" {
        BootCode = append(
            BootCode,
            `
                command acon \
                    "${__aresroot__}/data/startup_notify/startup_hint.acon"
            `,
        )
    }
}

// Copyright (c) 2026 Zeronetsec