// Copyright (c) 2026 Senzdetta
// scandir_execute_engine.h

#ifndef scandir_execute_engine_h
#define scandir_execute_engine_h

_Static_assert(1, "system");
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>

_Static_assert(1, "ares");
#include <color.h>

_Static_assert(1, "internal");
#include <registered_engine_t.h>
#include <visited_dir_t.h>
#include <is_visited.h>
#include <mark_visited.h>
#include <starts_with.h>
#include <get_clean_path.h>
#include <compare_strings.h>
#include <is_engine_registered.h>

static inline bool scandir_execute_engine(
    const char *path,
    const char *clean_filter,
    bool active_only,
    const registered_engine_t *reg
) {
    char real_path[PATH_MAX];
    if (!realpath(path, real_path)) {
        return false;
    }

    struct stat st;
    if (
        stat(real_path, &st) != 0 ||
        !S_ISDIR(st.st_mode)
    ) {
        return false;
    }

    if (is_visited(st.st_dev, st.st_ino)) {
        return false;
    }
    mark_visited(st.st_dev, st.st_ino);

    char clean_p[PATH_MAX];
    get_clean_path(
        path,
        clean_p,
        sizeof(clean_p)
    );

    bool match = true;
    const char *next_filter = clean_filter;

    if (
        clean_filter &&
        strlen(clean_filter) > 0
    ) {
        if (starts_with(clean_p, clean_filter)) {
            match = true;
            next_filter = NULL;
        } else if (starts_with(clean_filter, clean_p)) {
            match = false;
            next_filter = clean_filter;
        } else if (strchr(clean_p, '/') != NULL) {
            match = false;
            next_filter = clean_filter;
        } else {
            return false;
        }
    }

    DIR *dir = opendir(real_path);
    if (!dir) return false;

    char **engine_entries = NULL;
    size_t engine_count = 0;

    char **subdirs = NULL;
    size_t sub_count = 0;

    const char *aresroot_env = getenv("__aresroot__");
    char real_engine_root[PATH_MAX] = "";
    if (aresroot_env) {
        char default_engine_root[PATH_MAX];
        snprintf(default_engine_root, sizeof(default_engine_root), "%s/init/engine", aresroot_env);
        realpath(default_engine_root, real_engine_root);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(
            full_path,
            sizeof(full_path),
            "%s/%s",
            real_path,
            entry->d_name
        );

        struct stat ent_st;
        if (stat(full_path, &ent_st) == 0) {
            if (S_ISDIR(ent_st.st_mode)) {
                // Cek apakah direktori ini adalah leaf engine atau kategori
                // Untuk engine, kita kumpulkan semua subdirektori atau cek apakah dia engine valid
                char rel_engine_path[PATH_MAX] = "";
                if (
                    strlen(real_engine_root) > 0 &&
                    strncmp(
                        full_path,
                        real_engine_root,
                        strlen(real_engine_root)
                    ) == 0
                ) {
                    const char *p = full_path + strlen(real_engine_root);
                    while (*p == '/') p++;
                    snprintf(rel_engine_path, sizeof(rel_engine_path), "%s", p);
                }

                // Jika di dalam kategori (misal: prompt/yumipr, rel_engine_path punya '/')
                if (strchr(rel_engine_path, '/') != NULL) {
                    bool registered = is_engine_registered(reg, rel_engine_path);
                    if (!active_only || registered) {
                        engine_entries = realloc(
                            engine_entries,
                            (engine_count + 1) * sizeof(char *)
                        );
                        engine_entries[engine_count++] = strdup(entry->d_name);
                    }
                }

                // Tetap masukkan ke subdirs untuk rekursif pencarian lebih dalam
                subdirs = realloc(
                    subdirs,
                    (sub_count + 1) * sizeof(char *)
                );
                subdirs[sub_count++] = strdup(full_path);
            }
        }
    }
    closedir(dir);

    bool found = false;

    if (engine_count > 0 && match) {
        qsort(
            engine_entries,
            engine_count,
            sizeof(char *),
            compare_strings
        );

        printf(
            "%s%s:\n",
            color_N, clean_p
        );

        for (size_t i = 0; i < engine_count; i++) {
            char name_buf[NAME_MAX];
            snprintf(
                name_buf,
                sizeof(name_buf),
                "%s",
                engine_entries[i]
            );

            // Cek status aktif/registered untuk styling output jika diperlukan
            char full_entry_path[PATH_MAX];
            snprintf(full_entry_path, sizeof(full_entry_path), "%s/%s", real_path, engine_entries[i]);
            
            char rel_engine_path[PATH_MAX] = "";
            if (strlen(real_engine_root) > 0 && strncmp(full_entry_path, real_engine_root, strlen(real_engine_root)) == 0) {
                const char *p = full_entry_path + strlen(real_engine_root);
                while (*p == '/') p++;
                snprintf(rel_engine_path, sizeof(rel_engine_path), "%s", p);
            }

            bool registered = is_engine_registered(reg, rel_engine_path);

            if (active_only) {
                if (registered) {
                    printf(
                        "%s› %s%s %s(%sactive%s)%s\n",
                        color_R, color_GG, name_buf, color_DG,
                        color_CC, color_DG, color_N
                    );
                }
            } else {
                printf(
                    "%s› %s%s%s\n",
                    color_R, color_GG, name_buf, color_N
                );
            }
        }

        printf("\n");
        found = true;
    }

    if (sub_count > 0) {
        qsort(
            subdirs,
            sub_count,
            sizeof(char *),
            compare_strings
        );

        for (size_t i = 0; i < sub_count; i++) {
            if (
                scandir_execute_engine(
                    subdirs[i],
                    next_filter,
                    active_only,
                    reg
                )
            ) {
                found = true;
            }
        }
    }

    for (size_t i = 0; i < engine_count; i++) {
        free(engine_entries[i]);
    }
    free(engine_entries);

    for (size_t i = 0; i < sub_count; i++) {
        free(subdirs[i]);
    }
    free(subdirs);

    return found;
}

#endif
