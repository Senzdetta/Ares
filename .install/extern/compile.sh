function install::extern::compile() {
    local -a compile_targets=(
        "cso=${opt}/${targetins}/utils/cso"
        "go=${opt}/${targetins}/utils/go"
        "c=${opt}/${targetins}/bin"
        "go=${opt}/${targetins}/bin"
    )

    local has_checked_linux=false
    local item type target_dir

    for item in "${compile_targets[@]}"; do
        IFS='=' read -r type target_dir <<< "${item}"

        [[ -d "${target_dir}" ]] || continue

        local ext="c"
        [[ "${type}" == "go" ]] && ext="go"

        if [[
            "${type}" == "cso" && \
            "${has_checked_linux}" == false
        ]]; then
            install::extern::patching
            has_checked_linux=true
        fi

        (
            cd "${target_dir}" || exit 1
            command find . -type f -name "*.${ext}" | while read -r src_file; do
                local dir_path="$(
                    command dirname "${src_file}"
                )"

                local tool_name="$(
                    command basename "${dir_path}"
                )"

                local expected_src="${dir_path}/${tool_name}.${ext}"

                if [[ "${src_file}" == "${expected_src}" ]]; then
                    local full_src_dir="$(
                        command realpath -m \
                            "${target_dir}/${dir_path}"
                    )"

                    local parent_dir="$(
                        command dirname "${full_src_dir}"
                    )"

                    local temp_dir="${TMPDIR:-/tmp}"
                    local temp_bin="${temp_dir}/.${tool_name}_${RANDOM}.tmp"
                    local final_bin=""
                    local build_cmd=""
                    local display_name="${tool_name}"

                    if [[ "${type}" == "c" ]]; then
                        final_bin="${parent_dir}/${tool_name}"
                        build_cmd="
                            cd ${full_src_dir}
                            command gcc \
                                -O3 \
                                -march=native \
                                -flto \
                                -s ${tool_name}.c \
                                -o ${temp_bin} \
                                -I${opt}/${targetins}/lib/std/c \
                                -I${full_src_dir}
                        "

                    elif [[ "${type}" == "go" ]]; then
                        case "${tool_name}" in
                            'bootloader')
                                install::extern::hashing
                                ;;
                        esac

                        final_bin="${parent_dir}/${tool_name}"
                        build_cmd="
                            cd ${full_src_dir}
                            command go mod tidy
                            command go build -o ${temp_bin} .
                        "

                    elif [[ "${type}" == "cso" ]]; then
                        final_bin="${parent_dir}/${tool_name}.so"
                        display_name="${tool_name}.so"

                        local extra_flag=""
                        case "${tool_name}" in
                            'shgest') extra_flag="-lreadline" ;;
                        esac

                        build_cmd="
                            cd ${full_src_dir}
                            command gcc \
                                -fPIC \
                                -shared \
                                -O3 \
                                -march=native \
                                -s ${tool_name}.c \
                                -o ${temp_bin} \
                                -I${prefix}/include/bash \
                                -I${prefix}/include/bash/include \
                                -I${prefix}/include/bash/builtins \
                                -I${opt}/${targetins}/lib/std/c \
                                -I${full_src_dir} \
                                ${extra_flag}
                        "
                    fi

                    local rel_parent="${parent_dir##${opt}/${targetins}/}"
                    local log_path="${rel_parent}/${display_name}"

                    install::getinstall \
                        "${build_cmd}" \
                        "Compiling: ${color_GG}${type}${color_DG}:${color_GG}${log_path}${color_N}"

                    if [[ -f "${temp_bin}" ]]; then
                        command rm -rf "${full_src_dir}"
                        command mv "${temp_bin}" "${final_bin}"

                        if [[ "${type}" == "cso" ]]; then
                            local symlink_dir="${opt}/${targetins}/lib/std/shell/cso"
                            command mkdir -p "${symlink_dir}"

                            local actual="$(
                                command realpath -m \
                                    "${final_bin}"
                            )"

                            command ln -sf \
                                "${actual}" \
                                "${symlink_dir}/${tool_name}.so"
                        else
                            command chmod +x "${final_bin}"
                        fi
                    fi
                fi
            done
        )

        if [[ "${type}" == "cso" && "${__HDPATCHED__}" == true ]]; then
            unset __HDPATCHED__
            install::getinstall \
                "command mv ${targethd}.ares.bak ${targethd}" \
                "Restore: ${color_GG}${targethd}.ares.bak ${color_DG}-> ${color_GG}${targethd}${color_N}"
            unset targethd
        fi
    done

    install::extern::xxdh
    install::getinstall \
        "
            command gcc \
                -O3 \
                -flto \
                -march=native \
                -s ${opt}/${targetins}/${targetins}.c \
                -o ${opt}/${targetins}/${targetsyml} \
                -I ${opt}/${targetins} && \
                    command rm -rf \
                        ${opt}/${targetins}/${targetins}.c \
                        ${opt}/${targetins}/console/*.h \
                        ${opt}/${targetins}/module \
                        ${opt}/${targetins}/utils/*.h \
                        ${opt}/${targetins}/utils/embeded
        " \
        "Compiling: ${color_GG}${targetins}${color_N}"
}; readonly -f install::extern::compile