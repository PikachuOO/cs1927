// peterKydd
// 07/0703
// .h file for link lists sorting program 

#define LINE "\n***************************************\n"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct _list *List;

//create a list
List createList(void);


//creates a new nodeand inserts in position
void insertNode(List list, int position, int value);


//prepend node (add new node to front of list)
void prependNode(List newList, int value);

//append node (add a new node to end of list)
void appendNode(List newList, int value);

//delete node at selected position (while preserving the list structure)
void deleteNode(List newList, int position);

//swap two nodes at positions##
void swapNode(List newList, int position1, int position2);

//return number of nodes in list
int listLength(List newList);

//prints the list
void printList(List newList);

//prints the list in reverse
void printListReverse(List newList);

//return data of selected node
int getData(List newList, int position);
