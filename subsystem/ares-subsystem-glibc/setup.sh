echo -e "${color_B}[*] ${color_N}Injecting packages: ${color_GG}${root}/.install/packages.txt${color_N}"
echo '
bash
coreutils
findutils
bash-builtins-dev::{bash-builtins,bash-devel,bash-dev,-}
libbash-dev::{libbash,-}
clang
gcc::libllvm
libconfig-dev::libconfig
golang::golang-go
zip
unrar::unrar-free
git
sed
eza::exa -> eza
grep
tree
curl
aria2
libreadline-dev::{libreadline,readline-dev,readline}
libncurses-dev::{libncurses,ncurses,libncurses5-dev,libncurses5,ncurses5}
micro
fzf
bat
glow::-
luajit
xxd
' > "${root}/.install/packages.txt"

echo -e "${color_GG}Adding openfile config for shgest.conf: ${color_GG}${root}/config/openfile.conf${color}"
echo '
shgest.conf = $__aresroot__/config/shgest.conf
' >> "${root}/config/openfile.conf"