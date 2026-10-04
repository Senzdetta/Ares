function install::extern::patching() {
    echo -e "${color_YY}[!] ${color_N}A temporary Bash header compatibility patch may be required on some distributions."
    echo -e "${color_YY}[!] ${color_N}The installer will apply the patch before continuing."

    if [[ "${__FORCEYES__}" != true ]]; then
        read -p "$(
            echo -e "${color_YY}[!] ${color_N}Continue? (y/n): "
        )" userconfirm

        if [[ "${userconfirm}" == 'n' ]]; then
            return
        fi
    fi

    echo -e "${color_B}[*] ${color_N}Continue..."
    install::extern::patchBashHeader
}; readonly -f install::extern::patching