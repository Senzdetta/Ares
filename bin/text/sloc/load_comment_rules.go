// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "fmt"
    "embed"
    "strings"
    "github.com/hashicorp/hcl/v2/hclsimple"
)

//go:embed languages.hcl
var embeddedConfig embed.FS

func loadCommentRules(
    configPath string,
) (map[string][]LangBinding, error) {
    var content []byte
    var err error

    if configPath != "" {
        content, err = os.ReadFile(configPath)
        if err != nil {
            return nil, fmt.Errorf(
                "failed to read config file %s (%v)",
                configPath, err,
            )
        }
    } else {
        content, err = embeddedConfig.ReadFile("languages.hcl")
        if err != nil {
            return nil, fmt.Errorf(
                "failed to read embeded config (%v)",
                err,
            )
        }
    }

    var hclConfig ConfigFile
    err = hclsimple.Decode(
        "languages.hcl",
        content, nil, &hclConfig,
    )

    if err != nil {
        return nil, fmt.Errorf(
            "failed to parse hcl syntax (%v)",
            err,
        )
    }

    rulesMap := make(map[string][]LangBinding)
    for _, lang := range hclConfig.Languages {
        var parsedRules []CommentRule

        for _, pattern := range lang.Com {
            if idx := strings.Index(pattern, "{}"); idx != -1 {
                prefix := pattern[:idx]
                suffix := pattern[idx+2:]

                if suffix != "" {
                    parsedRules = append(
                        parsedRules,
                        CommentRule{
                            IsBlock: true,
                            BlockStart: prefix,
                            BlockEnd: suffix,
                        },
                    )
                } else {
                    parsedRules = append(
                        parsedRules,
                        CommentRule{
                            Single: prefix,
                            IsBlock: false,
                        },
                    )
                }
            }
        }

        for _, ext := range lang.Ext {
            rulesMap[ext] = append(
                rulesMap[ext],
                LangBinding{
                    LangName: lang.Name,
                    Rules: parsedRules,
                },
            )
        }
    }

    return rulesMap, nil
}

// Copyright (c) 2026 Senzdetta