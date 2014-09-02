# COMP1927 lab


CC=gcc
CFLAGS=-Wall -Werror -O

.PHONY: clean clobber

all: testArrayQueue testListQueue

testArrayQueue: testQueue.o arrayQueue.o
	$(CC) $(CFLAGS) -o testArrayQueue arrayQueue.o testQueue.o

testListQueue: testQueue.o listQueue.o
	$(CC) $(CFLAGS) -o testListQueue listQueue.o testQueue.o

arrayQueue.o: arrayQueue.c Queue.h
	$(CC) -c $(CFLAGS) arrayQueue.c

listQueue.o: listQueue.c Queue.h
	$(CC) -c $(CFLAGS) listQueue.c

testQueue.o: testQueue.c Queue.h
	$(CC) -c $(CFLAGS) testQueue.c

clean:
	rm -f *.o

clobber: clean
	rm testListQueue testArrayQueue
