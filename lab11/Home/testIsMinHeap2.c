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
    int i;
    int heap1[] = {0,2,10,8,11,12,9};
    int heap2[] = {0,3,10,20,11,10,50,21,12,11,10,10,100,51,22,23};


    printf("Test 1: Some valid heaps from 2,10,8,11,12,9\n");
    for(i=0; i< 7; i++){
        printf("Heap size %d\n",i);
        assert(isMinHeap(heap1,i));
    }

    printf("Test passed\n");
    printf("Test 2: 3,10,20,11,10,50,21,12,11,10,10,100,51,22,23\n");
    assert(isMinHeap(heap2,15));
    printf("passed\n");
}

void testInvalidMinHeaps(void){
     int heap1[] = {0,10,7,6};
     int heap2[] = {0,2,1,8,11,12,9};    
     int heap3[] = {0,2,10,8,11,12,9,7};
     int heap4[] = {0,2,10,8,11,12,7,9};

     printf("Test Invalid heap 1: 10,7,6\n");
     assert(!isMinHeap(heap1,3));
     printf("passed\n");

     printf("Test Invalid heap 2: 2,1,8,11,12,9\n");
     assert(!isMinHeap(heap2,6));
     printf("passed\n");

     printf("Test Invalid heap 3: 2,10,8,11,12,9,7\n");
     assert(!isMinHeap(heap3,7));
     printf("passed\n");

     printf("Test Invalid heap 4: 2,10,8,11,12,7,9\n");
     assert(!isMinHeap(heap4,7));
     printf("passed\n");
}
