#include <assert.h>
#include <stdio.h>

#include "isMinHeap.h"

void testValidMinHeaps(void);
void testInvalidMinHeaps(void);

int main(int argc, char * argv[]){
    testValidMinHeaps();
    testInvalidMinHeaps();
    return 0;
}


void testValidMinHeaps(void){
   int testNumber = 1;
   
   int heap1[] = {0,2,10};
   int heap2[] = {0, 1 ,10, 11, 15, 16, 17, 18, 25, 49, 50};
   int heap3[] = {0, 1 ,2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12 , 13, 14, 15, 16, 16, 16, 17, 18 , 19 , 20};
   
   printf("\nTesting valid heaps:\n");
   
   printf("\tTest %d: Valid heap of size 2:\t", testNumber++);
   assert(isMinHeap(heap1,2));
   printf("PASSED.\n");

   printf("\tTest %d: Valid heap of size 10:\t", testNumber++);
   assert(isMinHeap(heap2, 10));
   printf("PASSED.\n");
   
   printf("\tTest %d: Valid heap of size 10, including duplicates:\t", testNumber++);
   assert(isMinHeap(heap3, 23));
   printf("PASSED.\n");
   
   
   //ADD MORE TESTS HERE
}

void testInvalidMinHeaps(void){
   int testNumber = 1;
   
   int heap1[] = {4, 1, 7, 6};
   int heap2[] = {0, 1, 2, 3, 4, 5, 6 ,6, 5, 4, 3, 2, 1, 0};
   int heap3[] = {0,10, 9 , 8, 7, 6, 5, 4};
   int heap4[] = { 5, 4, 3, 2, 1, 0, -1, -2, -3, -4};
   int heap5[] = {-100, -1, 0, -1, -100};

   printf("\nTesting invalid heaps:\n");


   printf("\tTest %d Invalid heap of size 3:\t", testNumber++);
   assert(!isMinHeap(heap1,3));
   printf("PASSED.\n");
   
   printf("\tTest %d Invalid heap of size 13:\t", testNumber++);
   assert(!isMinHeap(heap2,12));
   printf("PASSED.\n");

   printf("\tTest %d Invalid heap of size 8:\t", testNumber++);
   assert(!isMinHeap(heap3,7));
   printf("PASSED.\n");
   
   printf("\tTest %d Invalid heap of size 10, including negatives:\t", testNumber++);
   assert(!isMinHeap(heap4,9));
   printf("PASSED.\n");
   
   printf("\tTest %d Invalid heap of size 5:\t", testNumber++);
   assert(!isMinHeap(heap5,5));
   printf("PASSED.\n");
     

     //ADD MORE TESTS HERE
}
