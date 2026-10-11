// https://github.com/Senzdetta/Ares

#include <stdio.h>
#include <batch_junk.h>
#include <lib/std/c/missing_argument.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        missing_argument("tojunk");
        return 1;
    }

    batch_junk(argv[1]);
    return 0;
}

// Copyright (c) 2026 Senzdetta