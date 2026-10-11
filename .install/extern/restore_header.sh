function install::extern::restoreHeader() {
    install::getinstall \
        "command mv ${targethd}.ares.bak ${targethd}" \
        "Restore: ${color_GG}${targethd}.ares.bak ${color_DG}-> ${color_GG}${targethd}${color_N}"

    if [[ "${1}" == '--noexit' ]]; then
        return
    fi

    exit 130
}; readonly -f install::extern::restoreHeader