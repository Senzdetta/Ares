function install::extern::updatePreinstall() {
    local en="${opt}/${targetins}/.laction/execute"
    if [[ "${__UPPRE__}" == true ]]; then
        if [[ -f "${en}/metaupdate.py" ]]; then
            if ! command -v python3 &>/dev/null; then
                echo -e "${color_B}[*] ${color_N}Installing: ${color_GG}python3${color_N}"
                install::zinstall "python3"
            fi

            command mkdir -p "${en}/metaupdate"
            command touch "${en}/metaupdate/forceup"
            command python3 "${en}/metaupdate.py"
        fi
    fi
}; readonly -f install::extern::updatePreinstall