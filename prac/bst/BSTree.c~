// BSTree.h ... implementation of binary search tree ADT
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"
#include "Queue.h"

#define TRUE 1
#define FALSE 0

typedef struct BSTNode *Link;

typedef struct BSTNode {
	int  value;
	Link left, right;
} BSTNode;

// make a new node containing a value
static
Link newBSTNode(int v)
{
	Link new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->value = v;
	new->left = new->right = NULL;
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL)
		/* do nothing */;
	else {
		dropBSTree(t->left);
		dropBSTree(t->right);
		free(t);
	}
}

// display a BSTree (sideways)
static
void doShowBSTree(BSTree t, int level)
{
	int i;
	if (t == NULL) return;
	doShowBSTree(t->right, level+1);
	for (i = 0; i < level; i++) printf("   ");
	// indicate leaves
	if (t->left == NULL && t->right == NULL)
		printf("!");
	printf("%d\n", t->value);
	doShowBSTree(t->left, level+1);
}
void showBSTree(BSTree t)
{
	doShowBSTree(t, 0);
}

// print values in infix order
void BSTreeInfix(BSTree t)
{
	if (t == NULL) return;
	BSTreeInfix(t->left);
	printf("%d ", t->value);
	BSTreeInfix(t->right);
}

// print values in prefix order
void BSTreePrefix(BSTree t)
{
	if (t == NULL) return;
	printf("%d ", t->value);
	BSTreePrefix(t->left);
	BSTreePrefix(t->right);
}

// print values in postfix order
void BSTreePostfix(BSTree t)
{
	if (t == NULL) return;
	BSTreePostfix(t->left);
	BSTreePostfix(t->right);
	printf("%d ", t->value);
}

// print values in level-order
void BSTreeLevelOrder(BSTree t)
{
   if (t == NULL){
      return;
   }else{
      Queue queue = newQueue();
      //BSTree temp = NULL;
      
      //put root node value into queue
      QueueJoin(queue, t);
      
      while(QueueIsEmpty(queue) != TRUE){
         
         //showQueue(queue);
         t = QueueLeave(queue);
         
         //print the value of node t (starts with root node,
         //moves to the next node as each queue element is popped off. 
         printf("%d ", t->value);
         
         if(t->left != NULL){
            QueueJoin(queue, t->left);
         }
         if(t->right != NULL){
            QueueJoin(queue, t->right);
         }
      }
   }         
   
}

// count #nodes in BSTree
int BSTreeNumNodes(BSTree t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNumNodes(t->left)
		         + BSTreeNumNodes(t->right);
}

// count #leaves in BSTree
int BSTreeNumLeaves(BSTree t)
{
   //if empty tree, then return 0, because no tree	
	if(t == NULL){
      return 0;
	//if left and right pointers are NULL, leaf has been found.
	}else if((t->left == NULL) && (t->right == NULL)){
		return 1;
	//recursively run throught the list, returning 1 each time a leaf is encountered.
	//reursively call this function at each left/right branch 	
	}else{
	   return ((BSTreeNumLeaves(t->left)) + (BSTreeNumLeaves(t->right)));
	}
}
// check whether a value is in a BSTree
int BSTreeFind(BSTree t, int v)
{
	if (t == NULL)
		return 0;
	else if (v < t->value)
		return BSTreeFind(t->left, v);
	else if (v > t->value)
		return BSTreeFind(t->right, v);
	else // (v == t->value)
		return 1;
}

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, int v)
{
	if (t == NULL)
		t = newBSTNode(v);
	else if (v < t->value)
		t->left = BSTreeInsert(t->left, v);
	else if (v > t->value)
		t->right = BSTreeInsert(t->right, v);
	return t;
}
