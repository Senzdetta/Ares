// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

func generateBootloader() {
    BootCode = append(
        BootCode,
        `
            builtin loadso : '(
                utils/cso/destroyf -> destroyf
                utils/cso/destroyso -> destroyso
                utils/cso/destroyv -> destroyv
                utils/cso/rhome -> rhome
                utils/cso/dynav -> dynav
                utils/cso/dynap -> dynap
                utils/cso/shmod -> shmod
                utils/cso/unreadonlyf -> unreadonlyf
                utils/cso/error -> error
                utils/cso/llsi -> llsi
                utils/cso/loadrc -> loadrc
            )'

            builtin rhome
            builtin dynav
            builtin dynap

            trap 'builtin error' ERR
        `,
    )

    if val, _ := readconf("remove_log", 1); val == "true" {
        target := Home + "/.ares_log/"
        if err := remake(target, 0755); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: failed to remove %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, target,
                color.DG, color.GG, err, color.DG, color.N,
            )
        }
    }

    if val, _ := readconf("remove_gscache", 1); val == "true" {
        target := Prefix + "/tmp/ares/goscript_cache/"
        if err := remake(target, 0755); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: failed to remove %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, target,
                color.DG, color.GG, err, color.DG, color.N,
            )
        }
    }

    if val, _ := readconf("remove_cscache", 1); val == "true" {
        target := Prefix + "/tmp/ares/cscript_cache/"
        if err := remake(target, 0755); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: failed to remove %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, target,
                color.DG, color.GG, err, color.DG, color.N,
            )
        }
    }

    if val, _ := readconf("remove_binext", 1); val == "true" {
        target := AresRoot + "/bin"
        if err := rmext(target); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: failed to remove extension %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, target,
                color.DG, color.GG, err, color.DG, color.N,
            )
        }
    }

    if val, _ := readconf("chmod_toolkit", 1); val == "true" {
        target := AresRoot + "/bin"
        if err := chmodf(target, 0755); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: failed to set permission %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, target,
                color.DG, color.GG, err, color.DG, color.N,
            )
        }
    }

    if val, _ := readconf("cnf", 1); val == "true" {
        cnfEngine, _ := readconf("cnf_engine", 1)
        BootCode = append(
            BootCode,
            `
                builtin unreadonlyf : '(
                    command_not_found_handle
                )' 2>/dev/null || true

                builtin destroyf : '(
                    command_not_found_handle
                )' 2>/dev/null || true
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

    if val, _ := readconf("prompt", 1); val == "true" {
        promptEngine, _ := readconf("prompt_engine", 1)
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

    if val, _ := readconf("suggestion", 1); val == "true" {
        if val, _ := readconf("suggestion", 2); val != "--force" {
            BootCode = append(
                BootCode,
                `
                    command acon \
                        "${__aresroot__}/data/startup_notify/suggestion.acon"
                `,
            )
        }

        suggestionEngine, _ := readconf("suggestion_engine", 1)
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

    cursorVal, _ := readconf("cursor", 1)
    if cursorVal != "native" && cursorVal != "" {
        if err := setcursor(cursorVal); err != nil {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: failed to set cursor %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, cursorVal,
                color.DG, color.GG, err, color.DG, color.N,
            )
        }
    }

    if val, _ := readconf("startup_hint", 1); val == "true" {
        BootCode = append(
            BootCode,
            `
                command acon \
                    "${__aresroot__}/data/startup_notify/startup_hint.acon"
            `,
        )
    }

    BootCode = append(
        BootCode,
        `
            trap - ERR

            builtin loadrc
            builtin shmod
            builtin llsi

            builtin destroyso : '(
                destroyf
                destroyv
                rhome
                dynav
                dynap
                shmod
                unreadonlyf
                error
                llsi
                loadrc
                loadso
            )'

            enable -d destroyso
        `,
    )
}

// Copyright (c) 2026 Senzdetta