// eratosthenes.c
// Řešení IJC-DU1, příklad a), 16.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Implementace Eratosthenova síta.

#include <math.h>
#include "bitarray.h"

//Funkce Eratosthenes pro nalezeni prvocisel
void Eratosthenes(bitarray_t pole) {
  unsigned long N = bitarray_size(pole);
  unsigned long sqrtN = (unsigned long)sqrt((double)N);
  
  //Nastav vsechny bity na 1
  bitarray_fill(pole, 1);
  bitarray_setbit(pole, 0, 0);
  bitarray_setbit(pole, 1, 0);

  for (unsigned long i = 2; i <= sqrtN; i++) {
      if (bitarray_getbit(pole, i) == 1)
        //Skrtni nasobky i a zacni od i*i
        for (unsigned long j = i*i; j < N; j+=i) {
              bitarray_setbit(pole, j, 0);
        }
  }

}


