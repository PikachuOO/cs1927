// useT.c ... client for BSTree ADT
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"

#define MAXVALS 1000
//#define DELETE
#define TRIM

int main(int argc, char *argv[])
{
	BSTree T;
	int i, n, nvals, v[MAXVALS];

	// Build tree from values in stdin
	T = newBSTree();
	nvals = 0;
	while (nvals < MAXVALS && scanf("%d",&n) == 1) {
		v[nvals++] = n;
		T = BSTreeInsert(T,n);
	}

	// Display information about constructed tree
	printf("Tree:\n");showBSTree(T);
	printf("\n#nodes = %d,  ",BSTreeNumNodes(T));
	printf("#leaves = %d\n",BSTreeNumLeaves(T));
	printf("Infix  : "); BSTreeInfix(T); printf("\n");
	printf("Prefix : "); BSTreePrefix(T); printf("\n");
	printf("Postfix: "); BSTreePostfix(T); printf("\n");
	printf("ByLevel: "); BSTreeLevelOrder(T); printf("\n");

	// Check correctness of tree

	// assume no duplicates => each value produces a node
	assert(nvals == BSTreeNumNodes(T));
	// every inserted value can be found
	for (i = 0; i < nvals; i++)
		assert(BSTreeFind(T,v[i]) != 0);
	// (hopefully) non-existent value cannot be found
	assert(BSTreeFind(T,-7654321) == 0);
   printf("TreeSum is %d\n",sumTree(T));
   //printf("IsBalanced: %d\n",isBalanced(T));
   
   printf("Tree height is: %d\n", treeHeight(T));
   #ifdef DELETE
      int deleteVal = 0;
      printf("Please enter a value to delete:\n");
      scanf("%d", &deleteVal);
      T = deleteNode(T, deleteVal);
   #endif

   #ifdef TRIM
      int level = 0;
      printf("Please enter a level to trim:\n");
      scanf("%d", &level);
      T = trimTree(T, level);
   #endif  
   
   printf("TreeSum is %d\n",sumTree(T)); 
   
   printf("IsBalanced: %d\n",isBalanced(T));
   
   showBSTree(T);
   //printf("\n");
   //printf("isBST: %d\n", isBST(T));
   printf("\n");
   
	return 0;
}

