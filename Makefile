CC=gcc
CFLAGS = -Wall -g

clean:
	rm -f *.o graph

all: graph

graph: main.o algo.o
	$(CC) $(CFLAGS) -o graph main.o algo.o

algo.o: algo.c graph.h
	$(CC) $(CFLAGS) -c algo.c

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c
