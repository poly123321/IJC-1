CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LIBS = -lm

all: primes primes-i no-comment

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

primes.o: primes.c bitarray.h error.h
	$(CC) $(CFLAGS) -c primes.c

eratosthenes.o: eratosthenes.c bitarray.h
	$(CC) $(CFLAGS) -c eratosthenes.c

primes-i: primes-i.o eratosthenes-i.o bitarray.o error.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

primes-i.o: primes.c bitarray.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

eratosthenes-i.o: eratosthenes.c bitarray.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

bitarray.o: bitarray.c bitarray.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitarray.c -o bitarray.o

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) $^ -o $@

no-comment.o: no-comment.c error.h
	$(CC) $(CFLAGS) -c no-comment.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

run: all
	ulimit -s unlimited || true; ./primes
	ulimit -s unlimited || true; ./primes-i

clean:
	rm -f primes primes-i no-comment *.o