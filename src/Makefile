# Makefile

CC=gcc
CFLAGS=-g -O2 -Wall -std=c99 -Wpedantic
LDFLAGS=   # -pg
LIBS=

all: splitmbox

splitmbox: splitmbox.o mbox.o split.o alloc.o

mbox.o: mbox.c mbox.h
alloc.o: alloc.c alloc.h
split.o: split.c split.h

clean:
	rm -f *.o splitmbox
