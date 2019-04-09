CC=gcc
CFLAGS=-gdwarf-2
BINS=Djikstra

all: $(BINS)

Djikstra: Djikstra.o testDjikstra.o
	$(CC) -o Djikstra Djikstra.o testDjikstra.o

PQ: PQ.o testPQself.o
	$(CC) -o PQ PQ.o testPQself.o

PQ.o: PQ.c PQ.h

testPQself.o: testPQself.c PQ.h

Djikstra.o: Djikstra.c Djikstra.h

testDjikstra.o: testDjikstra.c Djikstra.h

clean:
	rm -f $(BINS) *.o core
