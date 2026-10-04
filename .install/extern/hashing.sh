function install::extern::hashing() {
    local target=(
        "shell.sh"
        "bootloader.sh"
    )

    local loop
    for loop in "${target[@]}"; do
        echo "" >> "${opt}/${targetins}/utils/embeded/${loop}"

        command head -c 64 /dev/urandom | \
            command base64 -w 0 | \
            command sha256sum | \
            command cut -d ' ' -f 1 | \
            command sed 's/^/\n#/' \
            >> "${opt}/${targetins}/utils/embeded/${loop}"

        command sha256sum \
            "${opt}/${targetins}/utils/embeded/${loop}" | \
            command cut -d ' ' -f 1 \
            > "${opt}/${targetins}/utils/go/bootloader/hash/${loop%%.*}.hash"
    done
}; readonly -f install::extern::hashing