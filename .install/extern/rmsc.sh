function install::extern::rmsc() {
    local array=(
        "${opt}/${targetins}/${targetins}.c"
        "${opt}/${targetins}/console/*.h"
        "${opt}/${targetins}/module"
        "${opt}/${targetins}/utils/*.h"
        "${opt}/${targetins}/utils/embeded"
        "${opt}/${targetins}/utils/crawlpath"
    )

    local i
    for i in "${array[@]}"; do
        install::getinstall \
            "command rm -rf ${i}" \
            "Removing: ${color_GG}${i}${color_N}"
    done
}; readonly -f install::extern::rmsc