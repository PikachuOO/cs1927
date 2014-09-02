// pter kydd
// 17/10/13
// function to check if a heap is in min-order
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "isMinHeap.h"
//To compile, run and test
//gcc -Wall -Werror -O -o testIsMinHeap testIsMinHeap.c isMinHeap.c


//return 1 if the array heap with a sepcified number of items is in heap order 
//You must assume that the heap items are in indexes 1..heapSize and that index 0 
//is empty and not used to store items.
int isMinHeap(int heap[], int heapSize){
   assert(heap != NULL);

   //start with an offest of two - comparing 
   int heapElement = 2;
   int isOrdered = 1;

   while( heapElement < heapSize && isOrdered ){
      if(heap[heapElement - 1] > heap[heapElement]){
         isOrdered = 0;
      }
   }

    return isOrdered;
}
