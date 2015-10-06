# Makefile

CC=gcc
SH = bash
CFLAGS = -g
LDFLAGS = -lm

shell: shell.o parse.o
	gcc -lm $^ -o $@

parse.o: parse.c parse.h
	gcc -c $(CFLAGS) $< -o $@

clean:
	@rm *.o shell
