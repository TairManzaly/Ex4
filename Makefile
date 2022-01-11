CFLAGS = -Wall -g

clean:
	rm -f *.o graph

all: graph

graph: graph.o
	gcc $(CFLAGS) -o graph algo.o
algo.o: algo.c graph.h
	gcc $(CFLAGS) -c algo.c