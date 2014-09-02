// IntList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008
// Modified by Angela Finlayson, November, 2013

#ifndef INTLIST_H
#define INTLIST_H

#include <stdio.h>

// External view of IntList
// Implementation given in intList.c

typedef struct intListImp *IntList;

typedef struct dIntListImp *DIntList;

// create a new empty IntList
IntList newIntList(void);

// free up all space associated with list
void freeIntList(IntList);

// create an IntList by reading values from a file
// assume that the file is open for reading
IntList fScanIntList(FILE *);

// apppend one integer to the end of a list
void insertIntList(IntList, int);

// return number of elements in a list
int lengthIntList(IntList);

// make a physical copy of a list
// new list looks identical to original list
IntList copyIntList(IntList);

// display list as one integer per line on stdout
void printIntList(IntList);

// check sanity of an IntList
int checkIntList(IntList);

// check sanity of a DIntList
int checkDIntList(DIntList);

// displays doubly-linked list as one integer per line on stdout
void printDIntList(DIntList);

// displays doubly-linked list as one integer per line on stdout in reverse order
void printRevDIntList(DIntList);

// Creates a doubly linked list copy of a linked list
DIntList doublify(IntList);

// free a doubly linked list
void freeDIntList(DIntList);

#endif
