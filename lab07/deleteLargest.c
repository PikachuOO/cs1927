// Implement the deleteLargest function below
//
// Compile and test the function using
// gcc -Wall -Werror -o deleteLargest deleteLargest.c deleteLargestTest.o
// ./deleteLargest


#include <stdio.h>
#include <stdlib.h>
#include "deleteLargest.h"

typedef struct _treeNode {
  Item item;
  treeLink left, right;
} treeNode;


//Delete the largest item in the tree and return the resulting tree
//You must free the memory of the node that is deleted
//If the tree is empty simply return the empty tree
//For example
/*
//       5                 5
/       / \               /  \
//     2   7        ---> 2    7
//        / \                /
//       6   8              6
//
*/
//You may assume there are no duplicates in the tree

treeLink deleteLargest (treeLink tree) {
   
   if(tree != NULL){
      if (tree->right == NULL){
         treeLink current = tree;
         tree = tree->left;
         free(current);
      
      }else{
         treeLink current = tree;
         treeLink previous = NULL;
         
         while(current->right != NULL){
            previous = current;
            current = current->right;
         }
         
         if(current->left == NULL){
            previous->right = NULL;
         }else{
            previous->right = current->left;
         }
         
         //clean up 
         free(current);
      }
   }
   return tree;
}
