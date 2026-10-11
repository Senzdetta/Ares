// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "strings"
    "github.com/charmbracelet/bubbles/textinput"
    "github.com/Senzdetta/Ares/lib/std/go/color"
    tea "github.com/charmbracelet/bubbletea"
)

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
    var cmd tea.Cmd
    switch msg := msg.(type) {
        case tea.KeyMsg:
            switch msg.String() {
                case "ctrl+q":
                    return m, tea.Quit
                case "up":
                    if !m.editing {
                        m.savedStatus = ""
                        for {
                            m.cursor--
                            if m.cursor < 0 {
                                m.cursor = len(m.items) - 1
                            }
                            if !m.items[m.cursor].IsComment {
                                break
                            }
                        }
                    }
                case "down":
                    if !m.editing {
                        m.savedStatus = ""
                        for {
                            m.cursor++
                            if m.cursor >= len(m.items) {
                                m.cursor = 0
                            }
                            if !m.items[m.cursor].IsComment {
                                break
                            }
                        }
                    }
                case "enter":
                    if !m.items[m.cursor].IsComment {
                        if m.editing {
                            newValue := strings.TrimSpace(m.textInput.Value())
                            keyChanged := m.items[m.cursor].Key

                            m.items[m.cursor].Value = newValue
                            m.editing = false

                            err := saveCfg(m.configPath, m.items)
                            if err != nil {
                                m.savedStatus = color.R + "» " + color.N + "Failed save config"
                            } else {
                                m.savedStatus = color.GG + "» " + color.N + "Config saved"
                                logMessage := fmt.Sprintf(
                                    "\"Change %s => %s\"",
                                    keyChanged, newValue,
                                )
                                shell(
                                    "mklog",
                                    "chstartup",
                                    ":info",
                                    logMessage,
                                )
                            }
                        } else {
                            m.editing = true
                            m.textInput.SetValue(m.items[m.cursor].Value)
                            m.textInput.Focus()
                            return m, textinput.Blink
                        }
                    }
                case "ctrl+e":
                    if m.editing {
                        m.editing = false
                    }
            }
    }

    if m.editing {
        m.textInput, cmd = m.textInput.Update(msg)
        return m, cmd
    }

    return m, nil
}

// Copyright (c) 2026 Senzdetta