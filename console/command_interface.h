// https://github.com/Zeronetsec/Ares

#ifndef console_command_interface_h
#define console_command_interface_h

typedef struct {
    const char *flag;
    void (*execute)(int argc, char **argv);
} Command;

#endif

// Copyright (c) 2026 Zeronetsec