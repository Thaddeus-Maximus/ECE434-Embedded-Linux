# Makefile

main: togglegpio.c gpio-utils.c
	gcc -lsoc togglegpio.c gpio-utils.c -o togglegpio

all: main

run: all
	./togglegpio 50 0.1
