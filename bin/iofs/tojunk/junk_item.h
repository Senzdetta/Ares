// https://github.com/Senzdetta/Ares

#ifndef junk_item_h
#define junk_item_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <lib/std/c/color.h>
#include <sys/stat.h>
#include <exist_mode.h>
#include <clean_dir_contents.h>

static inline void junk_item(char *item) {
    while (*item == ' ') {
        item++;
    }

    if (strlen(item) == 0) {
        return;
    }

    char *colon = strchr(item, ':');
    if (!colon) {
        fprintf(
            stderr,
            "%s[!] %sInvalid format: %s%s%s\n",
            color_R, color_N, color_GG, item, color_N
        );
        return;
    }

    *colon = '\0';
    char *spec = item;
    char *target_path = colon + 1;

    int is_symlink = 0;
    char type = 0;
    int idx = 0;

    if (spec[idx] == 's') {
        is_symlink = 1;
        idx++;
    }

    if (spec[idx] == 'f' || spec[idx] == 'd') {
        type = spec[idx];
        idx++;
    } else {
        fprintf(
            stderr,
            "%s[!] %sInvalid type: %s%s%s\n",
            color_R, color_N, color_GG, spec, color_N
        );
        return;
    }

    mode_t parsed_mode = (mode_t)strtol(
        &spec[idx],
        NULL,
        8
    );
    mode_t current_mode = exist_mode(target_path);

    mode_t final_mode = parsed_mode;
    if (parsed_mode == 0) {
        if (current_mode != 0) {
            final_mode = current_mode;
        } else {
            final_mode = (type == 'd') ?
                0755 :
                0644;
        }
    }

    if (is_symlink) {
        char link_target[1024] = {0};
        if (
            lstat(target_path, NULL) == 0 ||
            access(target_path, F_OK) == 0
        ) {
            ssize_t len = readlink(
                target_path, link_target,
                sizeof(link_target) - 1
            );

            if (len != -1) {
                link_target[len] = '\0';
            } else {
                strncpy(
                    link_target, target_path,
                    sizeof(link_target) - 1
                );
            }

            unlink(target_path);

            if (symlink(link_target, target_path) == 0) {
                printf(
                    "%s[+] %sRecreated symlink: %s%s %s-> %s%s%s\n",
                    color_GG, color_N, color_GG, target_path, color_DG,
                    color_GG, link_target, color_N
                );
            } else {
                fprintf(
                    stderr,
                    "%s[!] %sRecreate symlink failed: %s%s%s\n",
                    color_R, color_N, color_GG, strerror(errno), color_N
                );
            }
        } else {
            if (type == 'd') {
                if (mkdir(target_path, final_mode) == 0) {
                    printf(
                        "%s[+] %sCreated directory (sd fallback): %s%s %s(%smode: %s0%o%s)%s\n",
                        color_GG, color_N, color_GG, target_path, color_DG,
                        color_WW, color_CC, final_mode, color_DG,
                        color_N
                    );
                } else {
                    fprintf(
                        stderr,
                        "%s[!] %sCreate directory (sd fallback) failed: %s%s%s\n",
                        color_R, color_N, color_GG, strerror(errno), color_N
                    );
                }
            } else {
                FILE *fp = fopen(target_path, "w");
                if (fp) {
                    fclose(fp);
                    chmod(target_path, final_mode);
                    printf(
                        "%s[+] %sCreated file (sd fallback): %s%s %s(%smode: %s0%o%s)%s\n",
                        color_GG, color_N, color_GG, target_path, color_DG,
                        color_WW, color_CC, final_mode, color_DG,
                        color_N
                    );
                } else {
                    fprintf(
                        stderr,
                        "%s[!] %sCreate file (sf fallback) failed: %s%s%s\n",
                        color_R, color_N, color_GG, strerror(errno), color_N
                    );
                }
            }
        }
        return;
    }

    if (type == 'f') {
        FILE *fp = fopen(target_path, "w");
        if (fp) {
            fclose(fp);
            chmod(target_path, final_mode);
            printf(
                "%s[+] %sTruncated file: %s%s %s(%smode: %s0%o%s)%s\n",
                color_GG, color_N, color_GG, target_path, color_DG,
                color_WW, color_CC, final_mode, color_DG,
                color_N
            );
        } else {
            fprintf(
                stderr,
                "%s[!] %sTruncate file failed: %s%s%s\n",
                color_R, color_N, color_GG, strerror(errno), color_N
            );
        }
        return;
    }

    if (type == 'd') {
        struct stat st;
        if (lstat(target_path, &st) == 0) {
            clean_dir_contents(target_path);
            chmod(target_path, final_mode);
            printf(
                "%s[+] %sEmptied directory: %s%s %s(%smode: %s0%o%s)%s\n",
                color_GG, color_N, color_GG, target_path, color_DG,
                color_WW, color_CC, final_mode, color_DG,
                color_N
            );
        } else {
            if (mkdir(target_path, final_mode) == 0) {
                printf(
                    "%s[+] %sCreated directory: %s%s %s(%smode: %s0%o%s)%s\n",
                    color_GG, color_N, color_GG, target_path, color_DG,
                    color_WW, color_CC, final_mode, color_DG,
                    color_N
                );
            } else {
                fprintf(
                    stderr,
                    "%s[!] %sCreate directory failed: %s%s%s\n",
                    color_R, color_N, color_GG, strerror(errno), color_N
                );
            }
        }
        return;
    }
}

#endif

// Copyright (c) 2026 Senzdetta