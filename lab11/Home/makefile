CC=gcc
CFLAGS=-Wall -Werror -g -std=c99
OBJS= testHunter.o hunter.o Graph.o HunterView.o Queue.o 

testHunterView : $(OBJS)
	$(CC) -o testHunter $(OBJS)

Graph.o :          Graph.c Graph.h cities.h playerData.h game.h HunterView.h	
Queue.o :          Queue.c Queue.h cities.h playerData.h game.h HunterView.h Item.h
HunterView.o :     HunterView.c cities.h game.h Graph.h Graph.c HunterView.h playerData.h	
hunter.o :         hunter.c HunterView.c cities.h game.h Graph.h Graph.c HunterView.h playerData.h
testHunter.o :     testHunter.c cities.h game.h Graph.h Graph.c HunterView.h playerData.h


clean :
	rm -f testHunterView $(OBJS) core *.dSYM
	rm -f hunter $(OBJS) core *.dSYM
