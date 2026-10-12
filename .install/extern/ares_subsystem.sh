function install::extern::aresSubsystem() {
    local subsystem_dir="${root}/subsystem"

    if [[ ! -d "${subsystem_dir}" ]]; then
        echo -e "${color_R}[!] ${color_N}Directory: ${color_GG}${subsystem_dir} ${color_N}not found!"
        exit 1
    fi

    local subsystems
    builtin mapfile -t subsystems < <(
        command find "${subsystem_dir}" \
            -mindepth 1 \
            -maxdepth 1 \
            -type d \
            -exec basename {} \; | \
                command sort
    )

    if [[ "${#subsystems}" -eq 0 ]]; then
        echo -e "${color_R}[!] ${color_N}No available subsystem on: ${color_GG}${subsystem_dir}${color_N}"
        exit 1
    fi

    echo -e "${color_N}Available Ares Framework Subsystems:"
    for i in "${!subsystems[@]}"; do
        echo -e "${color_N}$((i + 1)). ${color_GG}${subsystems[${i}]}${color_N}"
    done

    local ch
    local selected=""

    if [[ "${__SUBSYSTEM__}" == interactive ]]; then
        read -rp "$(echo -e "${color_N}Select the subsystem: ")" ch
    else
        ch="${__SUBSYSTEM__}"
    fi

    if [[ "${ch}" =~ ^[0-9]+$ ]] && (( ch >= 1 && ch <= ${#subsystems[@]} )); then
        selected="${subsystems[$((ch - 1))]}"
    else
        local sub
        for sub in "${subsystems[@]}"; do
            if [[ "${sub}" == "${ch}" ]]; then
                selected="${sub}"
                break
            fi
        done
    fi

    if [[ -n "${selected}" ]]; then
        echo -e "${color_B}[*] ${color_N}Selected subsystem: ${color_GG}${selected}${color_N}"
    else
        if [[ -z "${ch}" ]]; then
            echo -e "${color_YY}[!] ${color_N}No selected subsystem"
        else
            echo -e "${color_YY}[!] ${color_N}Invalid subsystem: ${color_GG}${ch}${color_N}"
        fi
        selected="ares-subsystem-crossp"
        echo -e "${color_YY}[!] ${color_N}Falling back to subsystem: ${color_GG}${selected}${color_N}"
    fi

    local procdir="${subsystem_dir}/${selected}"
    if [[ -f "${procdir}/setup.sh" ]]; then
        echo -e "${color_B}[*] ${color_N}Execute: ${color_GG}${procdir}/setup.sh${color_N}"
        source "${procdir}/setup.sh"
        command rm -f "${procdir}/setup.sh"
    fi

    if ! command -v rsync &>/dev/null; then
        echo -e "${color_B}[*] ${color_N}Installing: ${color_GG}rsync${color_N}"
        install::zinstall "rsync"
    fi

    install::getinstall \
        "
            command rsync \
                -ah \
                --remove-source-files \
                ${procdir}/ \
                ${root}/
        " \
        "Injecting subsystem: ${color_GG}${selected} ${color_DG}-> ${color_GG}${root}/${color_N}"

    command rm -rf "${subsystem_dir}"
}; readonly -f install::extern::aresSubsystem