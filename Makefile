# Projekt:	IFJ16
# Autori:	xsztef02 xsipos03 xszucs01 xstolj00


CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -O2

ifj16:  collections.c error.c framework.c  headers ial.c instructions.c interpret.c io.c lex anal.c main.c prec anal.c stack.c strings.c synt anal.c 
 tstree.c valgrind.c collections.h error.h framework.h ial.h instructions.h interpret.h io.h lex anal.h stack.h strings.h synt anal.h synt structures.h testing.h tstree.h valgrind.h 
	$(CC) $(CFLAGS)  collections.c error.c framework.c  headers ial.c instructions.c interpret.c io.c lex anal.c main.c prec anal.c stack.c strings.c synt anal.c testing.c tstree.c valgrind.c collections.h error.h framework.h ial.h instructions.h interpret.h io.h lex anal.h stack.h strings.h synt anal.h synt structures.h testing.h tstree.h valgrind.h -lm

