// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "github.com/Senzdetta/Ares/lib/std/go/color"
)

func generateBootloader() {
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

    if val, _ := readconf("home", 1); val != "" {
        BootCode = append(
            BootCode,
            fmt.Sprintf(
                `
                    export HOME=%s
                `,
                val,
            ),
        )
    }

    if err := dynav(); err != nil {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: failed to export dynamic variable %s(%s%v%s)%s\n",
            color.R, color.N, color.DG, color.GG, err, color.DG, color.N,
        )
    }

    if err := dynap(); err != nil {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: failed to export dynamic PATH %s(%s%v%s)%s\n",
            color.R, color.N, color.DG, color.GG, err, color.DG, color.N,
        )
    }

    if val, _ := readconf("cnf", 1); val == "true" {
        cnfEngine, _ := readconf("cnf_engine", 1)
        BootCode = append(
            BootCode,
            `
                unset -f command_not_found_handle > /dev/null || {
                    echo -e "\x1b[1;31m[!] \x1b[0mBootloader: failed to unset function \x1b[0;32mcommand_not_found_handle\x1b[0m"
                    echo -e "\x1b[1;31m[!] \x1b[0mBootloader: cnf engine cannot applied"
                }
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
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: prompt engine %s%s %snot supported on %sares-subsystem-crossp%s\n",
                color.R, color.N, color.GG, promptEngine, color.N, color.GG, color.N,
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
        suggestionEngine, _ := readconf("suggestion_engine", 1)
        if suggestionEngine == "shgest" {
            fmt.Fprintf(
                os.Stderr,
                "%s[!] %sBootloader: suggestion engine %s%s %snot supported on %sares-subsystem-crossp%s\n",
                color.R, color.N, color.GG, suggestionEngine, color.N, color.GG, color.N,
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

    if err := loadrc(); err != nil {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: failed to load rcfile %s(%s%v%s)%s\n",
            color.R, color.N, color.DG, color.GG, err, color.DG, color.N,
        )
    }

    if err := shmod(); err != nil {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: failed to load shmod %s(%s%v%s)%s\n",
            color.R, color.N, color.DG, color.GG, err, color.DG, color.N,
        )
    }

    if err := llsi(); err != nil {
        fmt.Fprintf(
            os.Stderr,
            "%s[!] %sBootloader: failed to load llsi module %s(%s%v%s)%s\n",
            color.R, color.N, color.DG, color.GG, err, color.DG, color.N,
        )
    }
}

// Copyright (c) 2026 Senzdetta