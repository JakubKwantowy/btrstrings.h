CC=gcc
CFLAGS=-Wall

LD=gcc
AR=ar

all: bin/btrstrings.a bin/test

test: all
	bin/test

bin/test: test.c btrstrings.h
	$(CC) $(CFLAGS) -o bin/test.o -c $(filter %.c, $^)
	$(LD) -o $@ bin/test.o

bin/%.a: bin/%.o
	$(AR) r $@ $^

bin/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $(filter %.c, $^)
