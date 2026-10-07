// https://github.com/Senzdetta/Ares

#ifndef utils_genboot_h
#define utils_genboot_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <utils/embeded_shell.h>
#include <utils/embeded_bootloader.h>
#include <utils/variable.h>
#include <utils/color.h>

static inline int genboot(void) {
    char console_dir[PATH_MAX];
    char init_dir[PATH_MAX];
    char shell_path[PATH_MAX];
    char bootloader_path[PATH_MAX];

    snprintf(
        console_dir, sizeof(console_dir),
        "%s/console",
        __aresroot__
    );

    snprintf(
        init_dir, sizeof(init_dir),
        "%s/init",
        __aresroot__
    );

    snprintf(
        shell_path, sizeof(shell_path),
        "%s/console/shell.sh",
        __aresroot__
    );

    snprintf(
        bootloader_path, sizeof(bootloader_path),
        "%s/init/bootloader.sh",
        __aresroot__
    );

    mkdir(console_dir, 0755);
    mkdir(init_dir, 0755);

    FILE *f_shell = fopen(shell_path, "wb");
    if (!f_shell) {
        fprintf(
            stderr,
            "%s[!] %sFailed to generate: %s%s%s\n",
            color_R, color_N, color_GG, shell_path, color_N
        );
        return -1;
    }

    fwrite(
        embeded_shell, 1,
        embeded_shell_size, f_shell
    );
    fclose(f_shell);

    FILE *f_boot = fopen(bootloader_path, "wb");
    if (!f_boot) {
        fprintf(
            stderr,
            "%s[!] %sFailed to generate: %s%s%s\n",
            color_R, color_N, color_GG, bootloader_path, color_N
        );
        return -1;
    }

    fwrite(
        embeded_bootloader, 1,
        embeded_bootloader_size, f_boot
    );
    fclose(f_boot);

    return 0;
}

#endif

// Copyright (c) 2026 Senzdetta