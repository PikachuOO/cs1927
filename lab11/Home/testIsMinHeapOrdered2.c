#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "isMinHeapOrdered.h"

void testIsMinHeapOrderedTrue(void);
void testIsMinHeapOrderedFalse(void);

int main (int argc, const char * argv[]) {
   testIsMinHeapOrderedTrue();
   testIsMinHeapOrderedFalse();

   printf ("All tests passed!\n");
  
   return EXIT_SUCCESS;
}


void testIsMinHeapOrderedTrue (void) {
   
   
   Link newTree = NULL;
   printf("Tests for trees that are heap ordered\n");
   printf("Test 1 : Empty tree\n");
   assert(isMinHeapOrdered(newTree));
   printf("Passed\n");

   newTree = malloc(sizeof(struct node));
   newTree->item = 9;
   newTree->left = NULL;
   newTree->right = NULL;
 
   printf("Test 2 : Tree size 1\n");
   assert(isMinHeapOrdered(newTree)); 
   printf("Passed\n");

   Link newNode;
   newNode = malloc(sizeof(struct node));
   newNode->item = 15;
   newNode->left = NULL;
   newNode->right = NULL;
   newTree->left = newNode;
     


   printf("Test 3 : Tree size 2\n");
   assert(isMinHeapOrdered(newTree) );
   printf("Passed\n");


   Link newNode2 = malloc(sizeof(struct node));
   newNode2->item = 20;
   newNode2->left = NULL;
   newNode2->right = NULL;
   newTree->right = newNode2;
   
   printf("Test 4 : Tree size 3\n");
   assert(isMinHeapOrdered(newTree) );
   printf("Passed\n");
   
   Link newNode3 = malloc(sizeof(struct node));
   newNode3->item = 25;
   newNode3->left = NULL;
   newNode3->right = NULL;
   newNode->left = newNode3;
  
   printf("Test 5 : tree size 4\n");
   assert(isMinHeapOrdered(newTree) );
   printf("Passed\n");
   
   Link newNode4 = malloc(sizeof(struct node));
   newNode4->item = 16;
   newNode4->left = NULL;
   newNode4->right = NULL;
   newNode->right = newNode4;
  
   printf("Test 6 : tree size 5\n");
   assert(isMinHeapOrdered(newTree) );
   printf("Passed\n");
   
   Link newNode5 = malloc(sizeof(struct node));
   newNode5->item = 20;
   newNode5->left = NULL;
   newNode5->right = NULL;
   newNode2->left = newNode5;
  
   printf("Test 7 : tree size 6 and duplicate\n");
   assert(isMinHeapOrdered(newTree) );
   printf("Passed\n");


   free(newNode5);
   free(newNode4);
   free(newNode3);
   free(newNode2);
   free(newNode);
   free(newTree);
}

void testIsMinHeapOrderedFalse (void) {

 
   Link newTree = NULL;
   printf("Tests for trees that are not heap ordered\n");
  

   newTree = malloc(sizeof(struct node));
   newTree->item = 9;
   newTree->left = NULL;
   newTree->right = NULL;
 
   

   Link newNode;
   newNode = malloc(sizeof(struct node));
   newNode->item = 8;
   newNode->left = NULL;
   newNode->right = NULL;
   newTree->left = newNode;     


   printf("Test 1 : Tree size 2\n");
   assert(!isMinHeapOrdered(newTree) );
   printf("Passed\n");

   newNode->item = 15;

   Link newNode2 = malloc(sizeof(struct node));
   newNode2->item = 1;
   newNode2->left = NULL;
   newNode2->right = NULL;
   newTree->right = newNode2;
   
   printf("Test 2 : Tree size 3\n");
   assert(!isMinHeapOrdered(newTree) );
   printf("Passed\n");
   
   newNode2->item = 20;
   
   
   Link newNode3 = malloc(sizeof(struct node));
   newNode3->item = 14;
   newNode3->left = NULL;
   newNode3->right = NULL;
   newNode->left = newNode3;
  
   printf("Test 3 : tree size 4\n");
   assert(!isMinHeapOrdered(newTree) );
   printf("Passed\n");
   
   newNode3->item = 25;
   
   Link newNode4 = malloc(sizeof(struct node));
   newNode4->item = 1;
   newNode4->left = NULL;
   newNode4->right = NULL;
   newNode->right = newNode4;
  
   printf("Test 4 : tree size 5\n");
   assert(!isMinHeapOrdered(newTree) );
   printf("Passed\n");
   
   newNode4->item = 16;
   
   Link newNode5 = malloc(sizeof(struct node));
   newNode5->item = 19;
   newNode5->left = NULL;
   newNode5->right = NULL;
   newNode2->left = newNode5;
  
   printf("Test 5 : tree size 6\n");
   assert(!isMinHeapOrdered(newTree) );
   printf("Passed\n");


   free(newNode5);
   free(newNode4);
   free(newNode3);
   free(newNode2);
   free(newNode);
   free(newTree);
   
  
   


  
   
  
}

