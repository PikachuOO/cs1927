//peterkydd
//27/13/13
//test file for queue.h

//#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Queue.h"

void testCreateQueue( void ); 
void testDestroyQueue( void ); 
void testGetQueue( void ); 
void testPutQueue( void ); 
void testQueueSize( void ); 

int main (int argc, char *argv[]){
   printf("*************************************\n");
   printf("Testing listQueue.c ...\n\n");

   testCreateQueue();
   testDestroyQueue();
   testGetQueue(); 
   testPutQueue(); 
   testQueueSize(); 

   printf("\ntestQueue.c PASSED.\n");
   printf("*************************************\n");
    return EXIT_SUCCESS;
}       


void testCreateQueue( void ){
   printf("Testing createQueue... ");
   Queue newQueue = createQueue();
   assert(newQueue != NULL);
   
   printf(" PASSED!\n");
}


void testDestroyQueue( void ){
   printf("Testing destroyQueue... ");
   Queue newQueue = createQueue();
   assert(newQueue != NULL);
   
   destroyQueue(newQueue);
   //assert(newQueue == NULL);
   
   printf("PASSED!\n");
} 

void testQueueSize( void ){
   printf("Testing queueSize... ");
   
   Queue newQueue = createQueue();
   assert(newQueue != NULL);   
   
   putQueue(newQueue, 0);
   assert( queueSize(newQueue) == 1);
   putQueue(newQueue, 1);
   assert( queueSize(newQueue) == 2);
   putQueue(newQueue, 2);
   assert( queueSize(newQueue) == 3);
   putQueue(newQueue, 3);
    
   assert( queueSize(newQueue) == 4);
   
   getQueue(newQueue);
   assert( queueSize(newQueue) == 3);
   getQueue(newQueue);
   assert( queueSize(newQueue) == 2);
   getQueue(newQueue);
   assert( queueSize(newQueue) == 1);
   getQueue(newQueue);
   assert( queueSize(newQueue) == 0);
   
   destroyQueue(newQueue);
     
   printf("   PASSED!\n");
} 


void testGetQueue( void ){
   //get queue returns data from the head node and deletes that node
   printf("Testing getQueue... ");
   
   Queue newQueue = createQueue();
   assert(newQueue != NULL);   
   
   putQueue(newQueue, 0);
   assert( queueSize(newQueue) == 1);
   putQueue(newQueue, 1);
   assert( queueSize(newQueue) == 2);
   putQueue(newQueue, 2);
   assert( queueSize(newQueue) == 3);
   putQueue(newQueue, 3);
   assert( queueSize(newQueue) == 4);
   
   #ifdef DEBUG
      printf("\n");
      printf("%d\n", getQueue(newQueue));
      printf("%d\n", getQueue(newQueue));
      printf("%d\n", getQueue(newQueue));
      printf("%d\n", getQueue(newQueue));
   #endif
   
   
   assert( getQueue(newQueue) == 0);
   assert( getQueue(newQueue) == 1);
   assert( getQueue(newQueue) == 2);
   assert( getQueue(newQueue) == 3);
   
   
   printf("    PASSED!\n");
} 
void testPutQueue( void ){
   printf("Testing putQueue... ");
   
   Queue newQueue = createQueue();
   assert(newQueue != NULL);   
   
   putQueue(newQueue, 0);
   assert( queueSize(newQueue) == 1);
   putQueue(newQueue, 1);
   assert( queueSize(newQueue) == 2);
   putQueue(newQueue, 2);
   assert( queueSize(newQueue) == 3);
   putQueue(newQueue, 3);
   assert( queueSize(newQueue) == 4);
   
   assert( getQueue(newQueue) == 0);
   assert( getQueue(newQueue) == 1);
   assert( getQueue(newQueue) == 2);
   assert( getQueue(newQueue) == 3);
   
   printf("    PASSED!\n");
} 


