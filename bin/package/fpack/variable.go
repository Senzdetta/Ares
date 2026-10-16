// https://github.com/Senzdetta/Ares

package main

import (
    "regexp"
)

var (
    BackendRegistry = make(map[string]string)
    BackendMacroRegex = regexp.MustCompile(
        `@([a-zA-Z0-9_-]+)\((.*?)\)`,
    )
)

// Copyright (c) 2026 Senzdetta