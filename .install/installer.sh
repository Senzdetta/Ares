function install::installer() {
    #install::extern::patching
    install::extern::compile
    install::extern::removeExt
    install::extern::setShebang

    install::getinstall \
        "command chmod +x -R ${opt}/${targetins}/data/yumipr/" \
        "Set permission for: ${color_GG}${opt}/${targetins}/data/yumipr/${color_N}"

    if [[ ! -d "${HOME}/.ares_log" ]]; then
        install::getinstall \
            "command mkdir -p ${HOME}/.ares_log" \
            "Create directory: ${color_GG}${HOME}/.ares_log${color_N}"
    fi

    if [[ ! -f "${HOME}/.aresrc" ]]; then
        install::getinstall \
            "command touch ${HOME}/.aresrc" \
            "Create file: ${color_GG}${HOME}/.aresrc${color_N}"
    fi

    if [[ ! -d "${HOME}/.ares/init/shmod" ]]; then
        install::getinstall \
            "command mkdir -p ${HOME}/.ares/init/shmod" \
            "Create directory: ${color_GG}${HOME}/.ares/init/shmod${color_N}"
    fi

    if [[ ! -d "${tmp}/goscript_cache" ]]; then
        install::getinstall \
            "command mkdir -p ${tmp}/${targetins}/goscript_cache" \
            "Create directory: ${color_GG}${tmp}/${targetins}/goscript_cache${color_N}"
    fi

    if [[ ! -d "${tmp}/cscript_cache" ]]; then
        install::getinstall \
            "command mkdir -p ${tmp}/${targetins}/cscript_cache" \
            "Create directory: ${color_GG}${tmp}/${targetins}/cscript_cache${color_N}"
    fi
}; readonly -f install::installer