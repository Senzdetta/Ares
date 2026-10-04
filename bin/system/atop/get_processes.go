// https://github.com/Senzdetta/Ares

package main

import (
    "sort"
    "strings"
    "github.com/shirou/gopsutil/v3/process"
)

func getProcesses(maxProcs int) []ProcInfo {
    procs, err := process.Processes()
    if err != nil {
        return nil
    }

    var procList []ProcInfo
    for _, p := range procs {
        cmdStr, err := p.Cmdline()
        if err != nil || strings.TrimSpace(cmdStr) == "" {
            cmdStr, err = p.Name()
            if err != nil {
                continue
            }
        }

        cpu, err := p.CPUPercent()
        if err != nil {
            continue
        }

        mem, err := p.MemoryPercent()
        if err != nil {
            continue
        }

        procList = append(procList, ProcInfo{
            PID: p.Pid,
            Name: cmdStr,
            CPU: cpu,
            Memory: mem,
        })
    }

    sort.Slice(
        procList,
        func(i, j int) bool {
            return procList[i].CPU > procList[j].CPU
        },
    )

    if maxProcs > 0 && len(procList) > maxProcs {
        return procList[:maxProcs]
    }

    return procList
}

// Copyright (c) 2026 Senzdetta