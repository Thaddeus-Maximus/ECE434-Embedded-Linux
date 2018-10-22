# Makefile
LDFLAGS=-lncurses

main: main.c gpio-utils.c
	gcc -lsoc main.c gpio-utils.c -o main -lncurses

all: main

run: all
	./main 10 20
