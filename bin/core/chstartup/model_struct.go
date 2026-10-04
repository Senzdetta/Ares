// https://github.com/Senzdetta/Ares

package main

import (
    "github.com/charmbracelet/bubbles/textinput"
)

type model struct {
    items []ConfigItem
    cursor int
    textInput textinput.Model
    editing bool
    savedStatus string
    configPath string
}

// Copyright (c) 2026 Senzdetta