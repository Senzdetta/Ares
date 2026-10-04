// https://github.com/Senzdetta/Ares

package main

func SSinit() {
    BootCode = append(
        BootCode,
        `
            builtin loadso : '(
                utils/cso/destroyf -> destroyf
                utils/cso/destroyso -> destroyso
                utils/cso/destroyv -> destroyv
                utils/cso/rhome -> rhome
                utils/cso/dynav -> dynav
                utils/cso/dynap -> dynap
                utils/cso/shmod -> shmod
                utils/cso/unreadonlyf -> unreadonlyf
                utils/cso/error -> error
                utils/cso/llsi -> llsi
                utils/cso/loadrc -> loadrc
            )'

            builtin dynap
            builtin rhome
            builtin dynav

            trap 'builtin error' ERR
        `,
    )
}

// Copyright (c) 2026 Senzdetta