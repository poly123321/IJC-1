// error.c
// Řešení IJC-DU1, příklad b), 16.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Modul pro výpis chybových hlášení.

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "error.h"

void error_exit(const char *text, ...) {
    va_list args;
    va_start(args, text);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, text, args);
    va_end(args);
    exit(1);
}

void warning(const char *text, ...) {
    va_list args;
    va_start(args, text);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, text, args);
    va_end(args);
}


