// useIntList.c - testing IntList data type

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "IntList.h"

void testEmptyList(void);
void testList(void);

int main(int argc, char *argv[]){
    testEmptyList();
    testList();
    printf("All passed!\n");
    return 0;
}   


void testEmptyList(void){
    IntList myEmptyList;
    DIntList myEmptyDList;

    printf("Testing with an emptyList");
    myEmptyList = newIntList();
    printIntList(myEmptyList);
    
    myEmptyDList = doublify(myEmptyList);
    printDIntList(myEmptyDList);
    printRevDIntList(myEmptyDList);
    
    assert(checkIntList(myEmptyList));
    assert(checkDIntList(myEmptyDList));
    printf("Passed!\n");
    freeIntList(myEmptyList);
    freeDIntList(myEmptyDList);

}

void testList(void){
    IntList myList;
    DIntList myDList;

    printf("Enter some list data ");
    myList = fScanIntList(stdin);
    printIntList(myList);

         
    myDList = doublify(myList);
    printDIntList(myDList);
    printRevDIntList(myDList);

    assert(checkIntList(myList));
    assert(checkDIntList(myDList));
    printf("Passed!\n");

    
    //clean up after ourselves
    freeIntList(myList);
    freeDIntList(myDList);
    
}     
