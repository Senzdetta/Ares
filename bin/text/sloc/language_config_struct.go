// https://github.com/Senzdetta/Ares

package main

type LanguageConfig struct {
    Name string `hcl:"name,label"`
    Ext []string `hcl:"ext"`
    Com []string `hcl:"com"`
}

// Copyright (c) 2026 Senzdetta