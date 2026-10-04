function install::extern::patchBashHeader() {
    export targethd="${prefix}/include/bash/externs.h"

    install::getinstall \
        "command cp ${targethd} ${targethd}.ares.bak" \
        "Backup: ${color_GG}${targethd} ${color_DG}-> ${color_GG}${targethd}.ares.bak${color_N}"

    local patch1='/print_select_command_head\|xtrace_print_select_command_head/s/^/\/\/ /'
    install::getinstall \
        "command sed -i '${patch1}' ${targethd}" \
        "Patch 1: ${color_GG}${patch1} ${color_DG}-> ${color_GG}${targethd}${color_N}"

    local patch2='/dprintf PARAMS/s/^/\/\/ /'
    install::getinstall \
        "command sed -i '${patch2}' ${targethd}" \
        "Patch 2: ${color_GG}${patch2} ${color_DG}-> ${color_GG}${targethd}${color_N}"

    local patch3='/gethostname PARAMS/s/^/\/\/ /'
    install::getinstall \
        "command sed -i '${patch3}' ${targethd}" \
        "Patch 3: ${color_GG}${patch3} ${color_DG}-> ${color_GG}${targethd}${color_N}"

    local patch4='/u_bits32_t get_urandom32/s/^/\/\/ /'
    install::getinstall \
        "command sed -i '${patch4}' ${targethd}" \
        "Patch 4: ${color_GG}${patch4} ${color_DG}-> ${color_GG}${targethd}${color_N}"

    echo -e "${color_B}[*] ${color_N}Patches applied."
    echo -e "${color_B}[*] ${color_N}Header will be restored after compilation completes."

    export __HDPATCHED__=true
}; readonly -f install::extern::patchBashHeader