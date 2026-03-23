// primes.c
// Řešení IJC-DU1, příklad a), 16.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Výpočet posledních 10 prvočísel do 444000000 pomocí Eratosthenes síta.

#include <stdio.h>
#include <time.h>
#include "bitarray.h"

void Eratosthenes(bitarray_t pole);

int main(void) {
    clock_t start = clock();

    bitarray_create(p, 444000000);  //lokální pole na zásobníku
    
    unsigned long N = bitarray_size(p);

    Eratosthenes(p);

    unsigned long last10[10] = {0};
    int count = 0;
    for (unsigned long i = N - 1; i >= 2 && count < 10; i--) {
        if (bitarray_getbit(p, i)) {
            last10[9 - count] = i;
            count++;
        }
    }

    for (int k = 0; k < 10; k++) {
        printf("%lu\n", last10[k]);
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
