// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fnmatch.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#include <lib/std/c/color.h>
#include <lib/std/c/missing_argument.h>
#include <is_number.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        missing_argument("rmline");
        return 1;
    }

    const char *filename = argv[1];
    const char *line_arg = NULL;
    const char *out_filename = NULL;

    for (int i = 2; i < argc; i++) {
        if (
            strcmp(argv[i], "--line") == 0 &&
            i + 1 < argc
        ) {
            line_arg = argv[i + 1];
            i++;
        } else if (
            strcmp(argv[i], "--out") == 0 &&
            i + 1 < argc
        ) {
            out_filename = argv[i + 1];
            i++;
        }
    }

    if (!line_arg) {
        missing_argument("rmline");
        return 1;
    }

    FILE *infile = fopen(filename, "r");
    if (!infile) {
        fprintf(
            stderr,
            "%s[!] %sFailed opening input file: %s%s%s\n",
            color_R, color_N, color_GG, strerror(errno), color_N
        );
        return 1;
    }

    bool use_temp = (out_filename == NULL);
    char temp_filename[512];

    FILE *outfile = NULL;

    if (use_temp) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        char stamp[32];
        strftime(
            stamp, sizeof(stamp),
            "%Y%m%d-%H%M%S",
            t
        );

        snprintf(
            temp_filename, sizeof(temp_filename),
            "%s.%s-%d.tmp",
            filename, stamp, (int)getpid()
        );

        outfile = fopen(temp_filename, "w");
    } else {
        outfile = fopen(out_filename, "w");
    }

    if (!outfile) {
        fprintf(
            stderr,
            "%s[!] %sFailed to create output file: %s%s%s\n",
            color_R, color_N, color_GG, strerror(errno), color_N
        );
        fclose(infile);
        return 1;
    }

    bool is_num_mode = is_number(line_arg);
    long target_line = is_num_mode ?
        atol(line_arg) :
        0;

    char *line = NULL;
    size_t len = 0;

    ssize_t read;
    long current_line = 0;

    while ((read = getline(&line, &len, infile)) != -1) {
        current_line++;
        bool should_delete = false;

        if (is_num_mode) {
            if (current_line == target_line) {
                should_delete = true;
            }
        } else {
            char *clean_line = strdup(line);
            size_t len_l = strlen(clean_line);

            if (len_l > 0 && clean_line[len_l - 1] == '\n') {
                clean_line[len_l - 1] = '\0';
            }

            if (len_l > 1 && clean_line[len_l - 2] == '\r') {
                clean_line[len_l - 2] = '\0';
            }

            if (fnmatch(line_arg, clean_line, 0) == 0) {
                should_delete = true;
            }

            free(clean_line);
        }

        if (!should_delete) {
            fputs(line, outfile);
        }
    }

    free(line);
    fclose(infile);
    fclose(outfile);

    if (use_temp) {
        if (rename(temp_filename, filename) != 0) {
            fprintf(
                stderr,
                "%s[!] %sFailed to replace filename: %s%s%s\n",
                color_R, color_N, color_GG, strerror(errno), color_N
            );
            remove(temp_filename);
            return 1;
        }
    }

    return 0;
}

// Copyright (c) 2026 Senzdetta