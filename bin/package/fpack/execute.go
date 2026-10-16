// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "os/exec"
)

func execute(pkg, customBackend string, isUninstall bool) int {
    if pkg == "" {
        return 1
    }

    if customBackend != "" {
        backends := strings.Split(customBackend, ",")
        for _, b := range backends {
            b = strings.TrimSpace(b)
            if b == "" {
                continue
            }

            if code := customPkgBackend(b, pkg); code == 0 {
                return 0
            }
        }
        return 1
    }

    runCmd := func(name string, args ...string) int {
        cmd := exec.Command(name, args...)
        if err := cmd.Run(); err != nil {
            if exitErr, ok := err.(*exec.ExitError); ok {
                return exitErr.ExitCode()
            }
            return 1
        }
        return 0
    }

    hasCmd := func(name string) bool {
        _, err := exec.LookPath(name)
        return err == nil
    }

    if hasCmd("pacman") {
        if isUninstall {
            return runCmd(
                "pacman", "-R", "--noconfirm", pkg,
            )
        }

        if hasCmd("paru") {
            return runCmd(
                "paru", "-S", "--noconfirm", pkg,
            )
        } else if hasCmd("yay") {
            return runCmd(
                "yay", "-S", "--noconfirm", pkg,
            )
        }

        return runCmd(
            "pacman", "-S", "--noconfirm", pkg,
        )
    } else if hasCmd("apt") {
        if isUninstall {
            return runCmd(
                "apt", "remove", "-y", pkg,
            )
        }

        return runCmd(
            "apt", "install", "-y", pkg,
        )
    } else if hasCmd("dnf") {
        if isUninstall {
            return runCmd(
                "dnf", "remove", "-y", pkg,
            )
        }

        return runCmd(
            "dnf", "install", "-y", pkg,
        )
    } else if hasCmd("zypper") {
        if isUninstall {
            return runCmd(
                "zypper", "rm", "-y", pkg,
            )
        }

        return runCmd(
            "zypper", "in", "-y", pkg,
        )
    } else if hasCmd("apk") {
        if isUninstall {
            return runCmd(
                "apk", "del", pkg,
            )
        }

        return runCmd(
            "apk", "add", pkg,
        )
    } else if hasCmd("flatpak") {
        if isUninstall {
            return runCmd(
                "flatpak", "uninstall", "-y", pkg,
            )
        }

        return runCmd(
            "flatpak", "install", "-y", pkg,
        )
    } else if hasCmd("snap") {
        if isUninstall {
            return runCmd(
                "snap", "remove", pkg,
            )
        }

        return runCmd(
            "snap", "install", pkg,
        )
    }

    return 1
}

// Copyright (c) 2026 Senzdetta