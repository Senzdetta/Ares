function install::extern::linuxCheck() {
    function __linux_check__() {
        if [[ -f "/etc/os-release" ]]; then
            local os_id="$(
                command grep -E '^ID=' /etc/os-release | \
                command cut -d= -f2 | \
                command tr -d '"'
            )"

            if [[ "${os_id}" =~ ^(ubuntu|debian|kali|parrot|fedora|arch|alpine|linux)$ ]]; then
                return 1
            fi
        fi

        if [[ ! "$(command whoami)" =~ ^u0_a[0-9]+ ]]; then
            if [[ "$(command id -u)" != "0" ]]; then
                return 1
            fi
        fi

        if [[ ! -f "/system/bin/linker" && ! -f "/system/bin/linker64" ]]; then
            return 1
        fi

        if [[ ! -d "/data/data/com.termux/files/home" ]]; then
            return 1
        fi

        if [[ -z "${PREFIX}" || "${PREFIX}" != *"/com.termux/"* || ! -d "${PREFIX}" ]]; then
            return 1
        fi

        if [[ -z "${TERMUX_VERSION}" ]]; then
            return 1
        fi

        return 0
    }

    if ! __linux_check__; then
        echo -e "${color_YY}[!] ${color_N}Linux environment detected."
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
    fi
}; readonly -f install::extern::linuxCheck