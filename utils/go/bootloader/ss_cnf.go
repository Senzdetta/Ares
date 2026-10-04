// https://github.com/Zeronetsec/Ares

package main

import (
    "fmt"
)

func SScnf() {
    if val, _ := Readconf("cnf", 1); val == "true" {
        cnfEngine, _ := Readconf("cnf_engine", 1)
        BootCode = append(
            BootCode,
            `
                builtin unreadonlyf : '(
                    command_not_found_handle
                )' || true

                builtin destroyf : '(
                    command_not_found_handle
                )' || true
            `,
        )

        BootCode = append(
            BootCode,
            fmt.Sprintf(
                "source \"${__aresroot__}/init/engine/cnf/%s.shx\" || true\n",
                cnfEngine,
            ),
        )
    }
}

// Copyright (c) 2026 Zeronetsec