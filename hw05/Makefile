.DEFAULT_GOAL := app.arm
CC := gcc
CFLAGS := -g
LINKER_FLAGS := -lstdc++

app.o : app.c
	$(CC) $(CFLAGS) -c app.c -o app.o

app.arm : app.o
	$(CC) $(LINKER_FLAGS) -g app.o -o app.arm

.PHONY : clean
clean :
	rm -rf app.arm app.o

.PHONY : all
all: app.arm
