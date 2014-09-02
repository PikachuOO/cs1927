CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=ST_bstree.o Item.o ST_client.o

ST_client : $(OBJS)
	$(CC) -o ST_client $(OBJS)

ST_client.o : ST_client.c ST.h Item.h

ST_bstree.o : ST_bstree.c ST.h Item.h

Item.o : Item.c Item.h 

clean :
	rm -f ST_client $(OBJS) core

