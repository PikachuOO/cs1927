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
   int heapElement = 0;
   int isOrdered = 1;
   
   
   if(heap != NULL){
   
      // heapsize+1 /2 allows us to remain within the constraints of the array
      // the heapSize +1 allows us to maipulate integer divison to reach the final node
      // in odd numbers array sizes
      while( heapElement < (heapSize+1)/2 && isOrdered ){
         
         //check left node (ie, array element 2*n)
         if(heap[heapElement] > heap[2*heapElement]){
            isOrdered = 0;
         }
         
         //check right node (ie, 2*n +1)
         if(heap[heapElement] > heap[2*heapElement+1]){
            isOrdered = 0;
         }
         
         heapElement++;
      }
   }
    return isOrdered;
}
