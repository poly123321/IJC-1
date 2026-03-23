// no-comment.c
// Řešení IJC-DU1, příklad b), 18.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Implementace statoveho automatu pro mazani komentaru v kodu

// Stavy:
// 0 - Normalni kod
//  1 - Mozny zacatek komentare (precten '/')
//  2 - Blokovy komentar /* ... */
//  3 - Mozny konec blokoveho komentare (precten '*')
//  4 - Retezcovy literal "..."
//  5 - Escape sekvence v retezci (\")
//  6 - Radkovy komentar // ...
//  7 - Znakovy literal '...'
//  8 - Escape sekvence ve znakovem literalu (\')
//  9 - Backslash na konci radku v radkovem komentari (pokracovani na dalsi radek)


#include <stdio.h>
#include <stdlib.h>
#include "error.h"
int main(int argc, char *argv[]){

int stav = 0; //pocatecni stav
int c;

if (argc == 2) {
        if (freopen(argv[1], "r", stdin) == NULL)
                error_exit("Nelze otevrit soubor: %s\n", argv[1]);
}

while ((c=getchar()) != EOF) {
        switch(stav) {
                case 0: if(c=='/') stav=1;
                        else if(c=='"') { stav=4; putchar(c); }
                        else if(c=='\'') { stav=7; putchar(c); }
                        else putchar(c);
                        break;

                case 1: if(c=='*') stav=2;
                        else if(c=='/') stav=6;
                        else { stav=0; putchar('/'); putchar(c); }
                        break;

                case 2: if(c=='*') stav=3;
                        break;
                        
                case 3: if(c=='/') { stav=0; putchar(' '); }
                        else if(c!='*') stav=2;
                        break;

                case 4: if(c=='\\') stav=5;
                        else if(c=='"') stav=0;
                        putchar(c);
                        break;

                case 5: stav=4;
                        putchar(c);
                        break;

                case 6: if(c=='\n') { stav=0; putchar(c); }
                        else if(c=='\\') stav=9;
                        break;

                case 7: if(c=='\\') { stav=8; putchar(c); }
                        else if(c=='\'') { stav=0; putchar(c); }
                        else putchar(c);
                        break;

                case 8: stav=7; putchar(c);
                        break;

                case 9: if(c=='\n') { stav=6; }
                        else { stav=6; }
                        break;
        }
}
if (stav == 1) putchar('/');
if (stav == 2 || stav == 3) error_exit("Neukonceny komentar\n");
if (stav == 4 || stav == 5) error_exit("Neukonceny retezec\n");
if (stav == 7 || stav == 8) error_exit("Neukonceny znakovy literal\n");

return 0;
}
