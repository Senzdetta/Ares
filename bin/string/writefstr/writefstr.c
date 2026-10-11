// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <color.h>
#include <is_numeric.h>
#include <print_unescaped.h>

int main(int argc, char *argv[]) {
    int target_fd = STDOUT_FILENO;
    int should_close_fd = 0;

    char *message = NULL;

    for (int i = 1; i < argc; i++) {
        if (
            strcmp(argv[i], "--fd") == 0 &&
            (i + 1) < argc
        ) {
            char *target = argv[i + 1];
            if (
                strcmp(target, "stdout") == 0 ||
                strcmp(target, "1") == 0
            ) {
                target_fd = STDOUT_FILENO;
            } else if (
                strcmp(target, "stderr") == 0 ||
                strcmp(target, "2") == 0
            ) {
                target_fd = STDERR_FILENO;
            } else if (is_numeric(target)) {
                target_fd = atoi(target);
            } else {
                int file_fd = open(
                    target,
                    O_WRONLY | O_CREAT | O_APPEND,
                    0644
                );

                if (file_fd != -1) {
                    target_fd = file_fd;
                    should_close_fd = 1;
                } else {
                    fprintf(
                        stderr,
                        "%s[!] %sFailed opening target file: %s%s%s\n",
                        color_R, color_N, color_GG, strerror(errno), color_N
                    );
                    return 1;
                }
            }
            i++; 
        } else if (
            strcmp(argv[i], "--str") == 0 &&
            (i + 1) < argc
        ) {
            message = argv[i + 1];
            i++;
        }
    }

    if (message != NULL) {
        print_unescaped(target_fd, message);
        fsync(target_fd);
    }

    if (should_close_fd) {
        close(target_fd);
    }

    return 0;
}

// Copyright (c) 2026 Senzdetta