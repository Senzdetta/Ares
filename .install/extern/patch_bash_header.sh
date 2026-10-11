function install::extern::patchBashHeader() {
    export targethd="${prefix}/include/bash/externs.h"
    trap install::extern::restoreHeader INT TERM HUP

    install::getinstall \
        "command cp ${targethd} ${targethd}.ares.bak" \
        "Backup: ${color_GG}${targethd} ${color_DG}-> ${color_GG}${targethd}.ares.bak${color_N}"

    local patch=(
        '/print_select_command_head\|xtrace_print_select_command_head/s/^/\/\/ /'
        '/dprintf PARAMS/s/^/\/\/ /'
        '/gethostname PARAMS/s/^/\/\/ /'
        '/u_bits32_t get_urandom32/s/^/\/\/ /'
    )

    local loopatch
    for loopatch in "${patch[@]}"; do
        install::getinstall \
            "command sed -i '${loopatch}' ${targethd}" \
            "Patching: ${color_GG}${loopatch} ${color_DG}-> ${color_GG}${targethd}${color_N}"
    done

    echo -e "${color_B}[*] ${color_N}Patches applied."
    echo -e "${color_B}[*] ${color_N}Header will be restored after compilation completes."

    export __HDPATCHED__=true
}; readonly -f install::extern::patchBashHeader