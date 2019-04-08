CC=gcc
CFLAGS=-gdwarf-2
BINS=PQ

all: $(BINS)

PQ: PQ.o testPQ.o
	$(CC) -o PQ PQ.o testPQ.o

PQ.o: PQ.c PQ.h

testPQ.o: testPQ.c PQ.h

clean:
	rm -f $(BINS) *.o core
