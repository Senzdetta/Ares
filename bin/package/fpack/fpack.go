// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "os"
    "strings"
    "path/filepath"
    "github.com/Senzdetta/Ares/lib/std/go/color"
    "github.com/Senzdetta/Ares/lib/std/go/missing_argument"
)

func main() {
    var installFlag string
    var uninstallFlag string
    var scriptFlag string
    var backendFlag string

    args := os.Args[1:]
    for i := 0; i < len(args); i++ {
        arg := args[i]
        var flagName, flagVal string

        if strings.Contains(arg, "=") {
            parts := strings.SplitN(arg, "=", 2)
            flagName = parts[0]
            flagVal = parts[1]
        } else {
            flagName = arg
            if i+1 < len(args) && !strings.HasPrefix(
                args[i+1], "-",
            ) {
                i++
                flagVal = args[i]
            }
        }

        switch flagName {
            case "--install":
                installFlag = flagVal
            case "--uninstall":
                uninstallFlag = flagVal
            case "--script":
                scriptFlag = flagVal
            case "--backend":
                backendFlag = flagVal
        }
    }

    if installFlag == "" && uninstallFlag == "" && scriptFlag == "" {
        missing_argument.Execute("fpack")
        os.Exit(1)
    }

    prefix := os.Getenv("PREFIX")
    if prefix == "" {
        prefix = "/usr"
    }

    binDir := filepath.Join(
        prefix, "bin",
    )
    _ = os.MkdirAll(binDir, 0755)

    if backendFlag != "" {
        parseBackendFlag(backendFlag)
    }

    isUninstall := uninstallFlag != ""
    targetPayload := installFlag
    if isUninstall {
        targetPayload = uninstallFlag
    }

    if targetPayload != "" {
        items := splitInstallString(targetPayload)
        processScriptLines(
            items, "", binDir, isUninstall,
        )
    }

    if scriptFlag != "" {
        if err := installPackages(
            scriptFlag, "", binDir, isUninstall,
        ); err != nil {
            fmt.Printf(
                "%s[!] %sFailed to open script: %s%s %s(%s%v%s)%s\n",
                color.R, color.N, color.GG, scriptFlag,
                color.DG, color.GG, err, color.DG, color.N,
            )
            os.Exit(1)
        }
    }
}

// Copyright (c) 2026 Senzdetta