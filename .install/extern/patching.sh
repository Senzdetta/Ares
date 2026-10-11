function install::extern::patching() {
    function __printwarn__() {
        echo -e "${color_YY}[!] ${color_N}A temporary Bash header compatibility patch may be required on some distributions."
        echo -e "${color_YY}[!] ${color_N}The installer will apply the patch before continuing."
    }

    function __input__() {
        read -p "$(
            echo -e "${color_YY}[!] ${color_N}Continue? (y/n): "
        )" userconfirm

        if [[ "${userconfirm}" == n ]]; then
            return
        fi

        echo -e "${color_B}[*] ${color_N}Continue..."
        install::extern::patchBashHeader
    }

    case "${__PATCH__}" in
        '')
            __printwarn__
            __input__
            ;;
        'interactive')
            __printwarn__
            __input__
            ;;
        'true')
            __printwarn__
            install::extern::patchBashHeader
            ;;
        'false')
            :
            ;;
        *)
            __printwarn__
            __input__
            ;;
    esac
}; readonly -f install::extern::patching