// bitarray.h
// Řešení IJC-DU1, příklad a), 16.3.2026
// Autor: Jan Polášek, FSI
// Přeloženo: gcc merlin
// Implementace maker a inline funkci pro prace s bitovymi poli.

#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "error.h"

typedef unsigned long *bitarray_t;
typedef unsigned long bitarray_index_t;

#define BA_WORD_BITS (sizeof(unsigned long) * CHAR_BIT)

//Inline funkce
#ifdef USE_INLINE

//Vraci pocet bitu pole
inline unsigned long bitarray_size(bitarray_t pole) {
    return pole[0];
}

//Vraci hodnotu bitu na indexu i
inline unsigned long bitarray_getbit(bitarray_t pole, bitarray_index_t i) {
#ifndef NO_CHECK
    if (i >= pole[0])
        error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)i, (unsigned long)pole[0]-1);
#endif
    return (pole[i / BA_WORD_BITS + 1] >> (i % BA_WORD_BITS)) & 1UL;
}

//Nastavi bit na indexu i na hodnotu 0 nebo 1
inline void bitarray_setbit(bitarray_t pole, bitarray_index_t i, int výraz) {
#ifndef NO_CHECK
    if (i >= pole[0])
        error_exit("bitarray_setbit: Index %lu mimo rozsah 0..%lu",
                   (unsigned long)i, (unsigned long)pole[0]-1);
#endif
    if (výraz)
        pole[i / BA_WORD_BITS + 1] |= (1UL << (i % BA_WORD_BITS));
    else
        pole[i / BA_WORD_BITS + 1] &= ~(1UL << (i % BA_WORD_BITS));
}

//Nastavi vsechny bity pole na 0 nebo 1
inline void bitarray_fill(bitarray_t pole, int hodnota) {
    unsigned long pocet = bitarray_size(pole) / BA_WORD_BITS + 1;
    for (unsigned long i = 1; i <= pocet; i++) {
        pole[i] = hodnota ? ~0UL : 0UL;
    }
}

//Definuje a nuluje lokalni pole na zasobniku
#define bitarray_create(p, i) \
    static_assert((i) > 0, "Velikost pole musi byt kladna"); \
    unsigned long p[(i) / BA_WORD_BITS + 2] = {0}; \
    p[0] = (i)

//Alokuje pole dyn. na halde
#define bitarray_alloc(p, i) \
    assert((i) <= (ULONG_MAX - 2) * BA_WORD_BITS); \
    unsigned long *p = calloc((i) / BA_WORD_BITS + 2, sizeof(unsigned long)); \
    if (p == NULL) \
        error_exit("bitarray_alloc: Chyba alokace paměti"); \
    p[0] = (i);

//Uvolnuje pamet
#define bitarray_free(p) free(p)

#else

//Makra
//Definuje a nuluje lokalni pole na zasobniku
#define bitarray_create(p, i) \
    static_assert((i) > 0, "Velikost pole musi byt kladna"); \
    unsigned long p[(i) / BA_WORD_BITS + 2] = {0}; \
    p[0] = (i)

//Vraci pocet bitu pole
#define bitarray_size(pole) (pole)[0]

#ifndef NO_CHECK
//Nastavi bit na indexu i
#define bitarray_setbit(pole, i, výraz) \
    (((i) >= bitarray_size(pole)) ? \
    (error_exit("bitarray_setbit: Index %lu mimo rozsah 0..%lu", \
    (unsigned long)(i), (unsigned long)bitarray_size(pole)-1), 0UL) : \
    ((výraz) ? \
    ((pole)[(i) / BA_WORD_BITS + 1] |= (1UL << ((i) % BA_WORD_BITS))) : \
    ((pole)[(i) / BA_WORD_BITS + 1] &= ~(1UL << ((i) % BA_WORD_BITS)))))
#else
#define bitarray_setbit(pole, i, výraz) ((výraz) ? \
    ((pole)[(i) / BA_WORD_BITS + 1] |= (1UL << ((i) % BA_WORD_BITS))) : \
    ((pole)[(i) / BA_WORD_BITS + 1] &= ~(1UL << ((i) % BA_WORD_BITS))))
#endif

#ifndef NO_CHECK
//Vraci hodnotu bitu na indexu i
#define bitarray_getbit(pole, i) \
    (((i) >= bitarray_size(pole)) ? \
    (error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu", \
    (unsigned long)(i), (unsigned long)bitarray_size(pole)-1), 0UL) : \
    (((pole)[(i) / BA_WORD_BITS + 1] >> ((i) % BA_WORD_BITS)) & 1UL))
#else
#define bitarray_getbit(pole, i) \
    (((pole)[(i) / BA_WORD_BITS + 1] >> ((i) % BA_WORD_BITS)) & 1UL)
#endif

//Nastavi vsechny bity pole na 0 nebo 1
#define bitarray_fill(pole, hodnota) do { \
    unsigned long pocet = bitarray_size(pole) / BA_WORD_BITS + 1; \
    for(unsigned long i = 1; i <= pocet; i++) { \
        pole[i] = (hodnota) ? ~0UL : 0UL; \
    } \
} while(0)

//Alokuje pole dyn. na halde
#define bitarray_alloc(p, i) \
    assert((i) <= (ULONG_MAX - 2) * BA_WORD_BITS); \
    unsigned long *p = calloc((i) / BA_WORD_BITS + 2, sizeof(unsigned long)); \
    if (p == NULL) \
        error_exit("bitarray_alloc: Chyba alokace paměti"); \
    p[0] = (i);

#define bitarray_free(p) free(p)

#endif  // USE_INLINE

#endif  // BITARRAY_H
