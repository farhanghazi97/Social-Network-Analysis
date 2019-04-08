CC=gcc
CFLAGS=-gdwarf-2
BINS=Graph

all: $(BINS)

Graph: Graph.o testGraph.o
	$(CC) -o Graph Graph.o testGraph.o

Graph.o: Graph.c Graph.h

testGraph.o: testGraph.c Graph.h

clean:
	rm -f $(BINS) *.o core
