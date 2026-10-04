// https://github.com/Zeronetsec/Ares

package main

func SSpostInit() {
    BootCode = append(
        BootCode,
        `
            trap - ERR

            builtin loadrc
            builtin shmod
            builtin llsi

            builtin destroyso : '(
                destroyf
                destroyv
                rhome
                dynav
                dynap
                shmod
                unreadonlyf
                error
                llsi
                loadrc
                loadso
            )'

            enable -d destroyso
        `,
    )
}

// Copyright (c) 2026 Zeronetsec