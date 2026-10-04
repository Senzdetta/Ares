# https://github.com/Senzdetta/Ares

function __fzf_envtool__() {
    local category
    local selected

    local fzf_opts=(
        --no-sort
        --exact
        --height 40%
        --layout=reverse
        --border
    )

    while true; do
        category="$(
            printf "tool\nfunction\nbuiltin\nalias\nvariable" | \
                command fzf "${fzf_opts[@]}" \
                    --query="${READLINE_LINE}" \
                    --prompt="Select Category > "
        )"

        [[ -z "${category}" ]] && return

        case "${category}" in
            'tool')
                selected="$(
                    compgen -c | \
                        command sort -u | \
                        command fzf "${fzf_opts[@]}" \
                            --prompt="Tools > "
                )"
                ;;
            'function')
                selected="$(
                    compgen -A function | \
                        command sort -u | \
                        command fzf "${fzf_opts[@]}" \
                            --prompt="Functions > "
                )"
                ;;
            'builtin')
                selected="$(
                    compgen -b | \
                        command sort -u | \
                        command fzf "${fzf_opts[@]}" \
                            --prompt="Builtins > "
                )"
                ;;
            'alias')
                selected="$(
                    compgen -a | \
                        command sort -u | \
                        command fzf "${fzf_opts[@]}" \
                            --prompt="Aliases > "
                )"
                ;;
            'variable')
                selected="$(
                    compgen -v | \
                        command sort -u | \
                        command fzf "${fzf_opts[@]}" \
                            --prompt="Variables > "
                )"
                ;;
        esac

        if [[ -n "${selected}" ]]; then
            READLINE_LINE="${selected}"
            READLINE_POINT=${#selected}
            break
        fi
    done
}; readonly -f __fzf_envtool__

# Copyright (c) 2026 Senzdetta