
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all debug release test mem_test clean

all: debug

release : CFLAGS += -g -O3
release : main

debug : CFLAGS += -g -O0
debug : main

test : CFLAGS += -g -O0
test : mem_test
	valgrind --track-origins=yes --leak-check=full ./mem_test

main: main.o gol.o
	$(CC) main.o gol.o -o main

mem_test: mem_test.o gol.o
	$(CC) mem_test.o gol.o -o mem_test
        
main.o: main.c gol.h
	$(CC) -c main.c
        
gol.o: gol.c gol.h
	$(CC) -c gol.c
        
mem_test.o: mem_test.c gol.h
	$(CC) -c mem_test.c
        
clean:
	rm *.o main mem_test