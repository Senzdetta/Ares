#!/usr/bin/env bash

set -o errexit

src="${BASH_SOURCE[0]}"
while [[ -h "${src}" ]]; do
    dir="$(
        cd -P "$(
            command dirname "${src}"
        )" > /dev/null 2>&1 && pwd
    )"
    src="$(command readlink "${src}")"
    [[ "${src}" != /* ]] && src="${dir}/${src}"
done

dir="$(
    cd -P "$(
        command dirname "${src}"
    )" > /dev/null 2>&1 && pwd
)"

export root="${dir}"; readonly root
source "${root}/.install/include.sh"

include : '(
    .install/color
    .install/variable
    .install/checker
    .install/error
    .install/getinstall
    .install/inpackages
    .install/installer
    .install/prepdir
    .install/zinstall
    .install/zparser
    .install/chmod
    .install/backup
    .install/rmov
    .install/symlink
    .install/zsymlink
    .install/extern/xcolor
    .install/extern/compile
    .install/extern/remove_ext
    .install/extern/patch_bash_header
    .install/extern/set_shebang
    .install/extern/hashing
    .install/extern/xxdh
    .install/extern/patching
    .install/extern/glow_install
    .install/extern/rmsc
    .install/extern/restore_header
    .install/extern/update_preinstall
    .install/extern/ares_subsystem
)'

HOME="${HOME}"
__BACKUP__=false
__PATCH__=interactive
__UPPRE__=false
__SUBSYSTEM__=interactive

while [[ ${#} -gt 0 ]]; do
    case "${1}" in
        "--home="*) export HOME="${1#*=}" ;;
        "--backup") export __BACKUP__=true ;;
        "--patch") export __PATCH__="${2}" ;;
        "--update-preinstall") export __UPPRE__=true ;;
        "--subsystem") export __SUBSYSTEM__="${2}" ;;
    esac
    shift
done

install::extern::aresSubsystem
install::inpackages
install::extern::glowInstall
install::prepdir
install::backup
install::rmov
install::installer
install::symlink
install::chmod
install::checker

trap - ERR EXIT
exit ${?}