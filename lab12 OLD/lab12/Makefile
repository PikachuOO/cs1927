CC=gcc
CFLAGS=-Wall -Werror -g

all: words

words: words.o Tree.o
	$(CC) $(CFLAGS) -o words words.o Tree.o

words.o: words.c Tree.h Item.h

tree.o: Tree.c Tree.h Item.h

clobber: clean
	rm -f words
clean:
	rm -f core *.o
