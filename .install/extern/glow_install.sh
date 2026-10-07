function install::extern::glowInstall() {
    if ! command -v glow &>/dev/null; then
        local repo="github.com/charmbracelet/glow@latest"

        if ! command -v go &>/dev/null; then
            echo -e "${color_B}[*] ${color_N}Installing: ${color_GG}golang::golang-go${color_N}"
            install::zparser "golang::golang-go"
        fi

        install::getinstall \
            "command go install ${repo}" \
            "Installing: ${color_GG}${repo} ${color_DG}-> ${color_GG}${bin}/glow${color_N}"

        if [[ -f "${HOME}/go/bin/glow" ]]; then
            if [[ ! -x "${HOME}/go/bin/glow" ]]; then
                command chmod +x "${HOME}/go/bin/glow"
            fi
            command ln -sf \
                "${HOME}/go/bin/glow" \
                "${bin}/glow"
        fi
    fi
}; readonly -f install::extern::glowInstall