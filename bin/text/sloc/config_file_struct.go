// https://github.com/Senzdetta/Ares

package main

type ConfigFile struct {
    Languages []LanguageConfig `hcl:"language,block"`
}

// Copyright (c) 2026 Senzdetta