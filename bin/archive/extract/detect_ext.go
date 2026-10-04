// https://github.com/Senzdetta/Ares

package main

import (
    "strings"
    "path/filepath"
)

func detectExt(filename string) string {
    f := strings.ToLower(
        filepath.Base(filename),
    )

    switch {
        case strEndsWithAny(
            f,
            ".tar.gz",
            ".tgz",
        ):
            return "tar.gz"
        case strEndsWithAny(
            f,
            ".tar.bz2",
            ".tbz2",
            ".tbz",
        ):
            return "tar.bz2"
        case strEndsWithAny(
            f,
            ".tar.xz",
            ".txz",
        ):
            return "tar.xz"
        case strEndsWithAny(
            f,
            ".tar.zst",
            ".tzst",
        ):
            return "tar.zst"
        default:
            ext := filepath.Ext(f)
            return strings.TrimPrefix(
                ext,
                ".",
            )
    }
}

// Copyright (c) 2026 Senzdetta