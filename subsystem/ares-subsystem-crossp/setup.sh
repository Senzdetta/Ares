echo -e "${color_B}[*] ${color_N}Disabling patching header: ${color_GG}${root}/.install/extern/patching.sh${color_N}"
echo '
function install::extern::patching() {
    if [[ "${__PATCH__}" != false ]]; then
        echo -e "${color_YY}Warning: ${color_N}patching header is not required for this subsystem.${color_N}"
    fi
}; readonly -f install::extern::patching
' > "${root}/.install/extern/patching.sh"

echo -e "${color_B}[*] ${color_N}Injecting packages: ${color_GG}${root}/.install/packages.txt${color_N}"
echo '
bash
coreutils
findutils
clang
gcc::libllvm
golang::golang-go
zip
git
sed
eza::exa -> eza
grep
tree
curl
aria2
micro
fzf
bat
glow::-
luajit
' > "${root}/.install/packages.txt"