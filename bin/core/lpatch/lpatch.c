// https://github.com/Senzdetta/Ares

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(1, "ares");
#include <color.h>
#include <missing_argument.h>

_Static_assert(1, "internal");
#include <mode.h>
#include <parse_args.h>
#include <get_init_paths.h>
#include <scan_llsi_state.h>
#include <patch_llsi_file.h>

#define MAX_LINE 4096
#define PATH_MAX_LEN 2048

int main(int argc, char *argv[]) {
    if (argc < 3) {
        missing_argument("lpatch");
        return 1;
    }

    Mode mode = MODE_NONE;
    char *group = NULL;
    char *mod_name = NULL;
    char *mod_val = NULL;

    parse_args(
        argc, argv,
        &mode, &group, &mod_name, &mod_val
    );

    if (mode == MODE_NONE || !group) {
        printf(
            "%s[!] %sInvalid args!\n",
            color_R, color_N
        );
        return 1;
    }

    char filename[PATH_MAX_LEN];
    char tmp_filename[PATH_MAX_LEN];
    get_init_paths(
        filename, sizeof(filename),
        tmp_filename, sizeof(tmp_filename)
    );

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf(
            "%s[!] %sFailed to open file: %s%s%s\n",
            color_R, color_N, color_GG, filename, color_N
        );
        return 1;
    }

    int group_found = 0;
    int mod_found = 0;
    int state_already_matched = 0;

    char group_header[256];
    snprintf(
        group_header, sizeof(group_header),
        "%s {", group
    );

    scan_llsi_state(
        f, mode, group, group_header, mod_name,
        &group_found, &mod_found, &state_already_matched,
        MAX_LINE
    );
    fclose(f);

    if (mode == MODE_CREATE) {
        if (group_found) {
            printf(
                "%s[!] %sGroup: %s%s %sis already exist!\n",
                color_R, color_N, color_GG, group, color_N
            );
            return 1;
        }
    } else {
        if (!group_found) {
            printf(
                "%s[!] %sGroup: %s%s %snot found!\n",
                color_R, color_N, color_GG, group, color_N
            );
            return 1;
        }

        if (mod_name && !mod_found) {
            printf(
                "%s[!] %sModule: %s%s %snot found in group %s%s%s\n",
                color_R, color_N, color_GG, mod_name, color_N,
                color_GG, group, color_N
            );
            return 1;
        }

        if (mod_name && state_already_matched) {
            printf(
                "%s[!] %sModule: %s%s %sis already %s%s%s\n",
                color_R, color_N, color_GG, mod_name, color_N,
                color_GG, (
                    mode == MODE_DISABLE ?
                    "disabled" :
                    "enabled"
                ),
                color_N
            );
            return 1;
        }
    }

    f = fopen(filename, "r");
    FILE *tmp = fopen(tmp_filename, "w");
    if (!f || !tmp) {
        perror("failed to processing temporary file!");
        if (f) fclose(f);
        if (tmp) fclose(tmp);
        return 1;
    }

    patch_llsi_file(
        f, tmp, mode, group, group_header,
        mod_name, mod_val, MAX_LINE
    );

    fclose(f);
    fclose(tmp);

    remove(filename);
    rename(tmp_filename, filename);

    printf(
        "%s[+] %sPatched: %s%s%s\n",
        color_GG, color_N, color_GG, filename, color_N
    );

    return 0;
}

// Copyright (c) 2026 Senzdetta