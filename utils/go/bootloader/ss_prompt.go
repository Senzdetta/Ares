// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
)

func SSprompt() {
    if val, _ := Readconf("prompt", 1); val == "true" {
        promptEngine, _ := Readconf("prompt_engine", 1)
        if promptEngine == "catchypr" {
            BootCode = append(
                BootCode,
                `
                    builtin loadso : '(
                        utils/cso/catchypr -> catchypr
                    )'
                `,
            )
        }

        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "source \"${__aresroot__}/init/engine/prompt/%s.shx\" || true\n",
                promptEngine,
            ),
        )
    }
}

// Copyright (c) 2026 Senzdetta