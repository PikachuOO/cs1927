// peterKydd
// 07/0703
// interface functions for link lists sorting program 

#define DEBUG

#include "ListSort.h"

typedef struct _node *nodePointer;

typedef struct _node {
   int data;
   nodePointer next;
   nodePointer previous;
} node;

typedef struct _list {
   int size;
   nodePointer first;
   nodePointer last;
} list;

List createList (void) {
   List new = malloc (sizeof (struct _list));
   new->first = NULL;
   new->last = NULL;
   return new;
}

void prependNode(List list, int value){
   
   nodePointer newNode = malloc(sizeof(struct _node));
   newNode->previous = NULL;
   newNode->next = NULL;
   newNode->data = value;
   
   list->size++;
   
   if(list->size > 1){
      list->first->previous = newNode;
   }
   
   if(list->last == NULL){
      list->last = newNode;
   }
   
   
   
   newNode->next = list->first;
   list->first = newNode;
   
   
   
}

/*
void appendNode(List newList, int value){
}


if(newList->size > 2){
      newList->first->next->previous = newNode;
      
      #ifdef DEBUG
         printf("Assigning previous node pointer.");
      #endif
   }

*/





























void printList(List newList){
   
   nodePointer current = newList->first;
   
   printf("[LIST_FIRST]>");
   
   while(current != NULL){
      printf("[%d]>", current->data);
      current = current->next;
   }
   printf("[X]\n");
}


void printListReverse(List newList){
   nodePointer current = newList->last;
   
   printf("[LIST_LAST-]>");
   
   while(current != NULL){
      printf("[%d]>", current->data);
      current = current->previous;
   }
   printf("[X]\n");
}

int listSize (List list){
   return list->size;
}


