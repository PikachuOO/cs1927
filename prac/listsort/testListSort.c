// peterKydd
// 07/0703
// test functions for link lists sorting program 

#include "ListSort.h"

void testCreateList(void);
//void testPrependNode(void);


int main (int argc, char *argv[]){
   printf(LINE);
   printf("Testing listSort...\n");
   
   testCreateList();   
   //printf("listSort PASSED.");
   printf(LINE);
   
   return EXIT_SUCCESS;
}



void testCreateList(void){
   printf("\tTesting createList...");
   
   List list = createList();
   
   prependNode(list, 3);
   prependNode(list, 2);
   prependNode(list, 1);
   prependNode(list, 0);
   
   printf("\n");

   printList(list);
   printListReverse(list);
   //printf("\tPASSED.\n");
}

















/*
void testPrependNode(void){
   printf("\tTesting createList...");
   
   List newList = createList();
   
   //prependNode(newList, 0);
   
   assert(newList->first != NULL);
   
   printf("PASSED");   
}
*/
