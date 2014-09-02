CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=useT.o BSTree.o Queue.o

all : useT mkprefix mkrandom

useT : $(OBJS)
	$(CC) -o useT $(OBJS)

useT.o : useT.c BSTree.h
BSTree.o : BSTree.c BSTree.h Queue.h
Queue.o : Queue.c Queue.h

mkprefix : mkprefix.c
	$(CC) $(CFLAGS) -o mkprefix mkprefix.c

mkrandom : mkrandom.c
	$(CC) $(CFLAGS) -o mkrandom mkrandom.c

clean :
	rm -f useT mkprefix mkrandom $(OBJS) core
