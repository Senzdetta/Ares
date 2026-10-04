function install::extern::xxdh() {
    local target=(
        "banner.txt"
        "shell.sh"
        "bootloader.sh"
    )

    local loop
    for loop in "${target[@]}"; do
        install::getinstall \
            "
                command xxd -i \
                    < ${opt}/${targetins}/utils/embeded/${loop} \
                    > ${opt}/${targetins}/utils/embeded/${loop%%.*}.h
            " \
            "Generate: ${color_GG}${opt}/${targetins}/utils/embeded/${loop%%.*}.h${color_N}"

        command rm -f \
            "${opt}/${targetins}/utils/embeded/${loop}"
    done

}; readonly -f install::extern::xxdh