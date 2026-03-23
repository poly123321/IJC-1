// error.h
// Řešení IJC-DU1, příklad b), 16.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Hlavickovy soubor pro error.c

#ifndef ERROR_H
#define ERROR_H

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif
