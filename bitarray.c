// bitarray.c
// Řešení IJC-DU1, příklad a), 16.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Extern inline funkce

#include "bitarray.h"

//Externí definice
extern inline unsigned long bitarray_size(bitarray_t pole);
extern inline unsigned long bitarray_getbit(bitarray_t pole, bitarray_index_t i);
extern inline void bitarray_setbit(bitarray_t pole, bitarray_index_t i, int výraz);
extern inline void bitarray_fill(bitarray_t pole, int hodnota);

