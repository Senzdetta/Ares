// https://github.com/Senzdetta/Ares

#ifndef handle_ls_h
#define handle_ls_h

#include <stdio.h>
#include <stdlib.h>

#include <lib/std/c/color.h>

#include <group.h>
#include <module.h>
#include <parse_init_file.h>
#include <free_groups.h>

static inline void handle_ls(
    const char *filepath,
    int show_mod
) {
    Group *groups = NULL;
    int group_count = 0;
    parse_init_file(
        filepath,
        &groups,
        &group_count
    );

    if (group_count == 0) {
        printf(
            "%s[!] %sFile: %s%s %sis empty or not exist!\n",
            color_R, color_N, color_GG, filepath, color_N
        );

        if (groups) {
            free_groups(groups, group_count);
        }

        return;
    }

    for (int i = 0; i < group_count; i++) {
        if (!show_mod) {
            printf(
                "%s› %sgroup: %s%s %s(%s%s%s)%s\n",
                color_R, color_N, color_GG, groups[i].name,
                color_DG,
                groups[i].is_disabled ?
                    color_YY :
                    color_CC,
                groups[i].is_disabled ?
                    "disabled" :
                    "active",
                color_DG, color_N
            );
        } else {
            printf(
                "%s› %sgroup: %s%s %s(%s%s",
                color_R, color_N, color_GG, groups[i].name,
                color_DG,
                groups[i].is_disabled ?
                    color_YY :
                    color_CC,
                groups[i].is_disabled ?
                    "disabled" :
                    "active"
            );

            if (groups[i].mod_count == 0) {
                printf(
                    ", no mod%s)%s\n",
                    color_DG, color_N
                );
            } else {
                printf(
                    "%s)%s\n",
                    color_DG, color_N
                );

                for (int j = 0; j < groups[i].mod_count; j++) {
                    Module *m = &groups[i].mods[j];
                    printf(
                        "  %s› %smod: %s%s ",
                        color_B, color_N, color_GG, m->raw_line
                    );

                    if (groups[i].is_disabled) {
                        if (m->is_disabled) {
                            printf(
                                "%s(%sdisabled%s)%s\n",
                                color_DG, color_YY, color_DG, color_N
                            );
                        } else {
                            printf(
                                "%s(%sactive no load, group is disabled%s)%s\n",
                                color_DG, color_CC, color_DG, color_N
                            );
                        }
                    } else {
                        if (m->is_disabled) {
                            printf(
                                "%s(%sdisabled%s)%s\n",
                                color_DG, color_YY, color_DG, color_N
                            );
                        } else {
                            printf(
                                "%s(%sactive%s)%s\n",
                                color_DG, color_CC, color_DG, color_N
                            );
                        }
                    }
                }
            }
        }
    }
    free_groups(groups, group_count);
}

#endif

// Copyright (c) 2026 Senzdetta