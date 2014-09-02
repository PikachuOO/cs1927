// BSTree.h ... implementation of binary search tree ADT
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"
#include "Queue.h"

#define TRUE 1
#define FALSE 0

static int max(int a, int b);
static int doTreeHeight(BSTree tree);

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

static Link join(Link left, Link right){
   Link returnVal;
   
   if( left == NULL && right == NULL){
      returnVal = NULL;
   }else if( left != NULL && right == NULL ){
      returnVal = left;   
   } else if ( left == NULL && right != NULL ) {
      returnVal = right;
   }else{
      Link current = NULL;
      Link previous = NULL;
      
      //find the left-most node of the right subtree
      for(current = right; current->left != NULL; current = current->left){
         previous = current;
      }
      
      if(previous != NULL){
         previous->left = current->right;
         current->right = right;
      }
   
      current->left = left;   
      returnVal = current;
   }
   
   
   return returnVal;
}


Link doDeleteNode(Link n, int key){
    Link returnVal = n;
    
    if(n != NULL){
       // traverse left
       if(key < n->value){
          returnVal->left = doDeleteNode(n->left, key);
       // traverse right
       } else if(key > n->value){
          returnVal->right = doDeleteNode(n->right, key);
       
       // we have found the node to delete   
       }else{
          Link left = n->left;
          Link right = n->right;
          free(n);
          returnVal = join(left, right);
       }
    }
    return returnVal;           
}

//delete the node with the specified value
// if value is not discovered, print error message          
Link deleteNode(Link t, int key){
   assert(t != NULL);
   Link returnVal = doDeleteNode(t, key);

   return returnVal;
}

static int max(int a, int b){
   int max = a;
   if(b > a){
      max = b;
   }
   return max;
}


static int doTreeHeight(BSTree t){
   int height = 0;
   int leftHeight = 0;
   int rightHeight = 0;

   if(t != NULL){
      height = 1;
      leftHeight = treeHeight(t->left);
      rightHeight = treeHeight(t->right);
    
      height = height + max(leftHeight, rightHeight);
   }
   return height;
}

int treeHeight(BSTree t){
   int height = -1;
   
   if(t != NULL){
      height = 0;
      height = doTreeHeight(t);
   }

   return height;
}

static int maxVal(BSTree t){
   assert(t != NULL);
   while(t != NULL){
   t = t->right;
   }
   
   return t->value;
}

static int minVal(BSTree t){
   assert(t != NULL);
   while(t != NULL){
   t = t->left;
   }
   
   return t->value;
}


static int doIsBST(BSTree tree){
   int BST = TRUE;
   
   if(tree != NULL){
      int left = TRUE;
      int right = TRUE;
      
      if(tree->left != NULL){
         left = (tree->left->value < tree->value); 
      }
      if(tree->right != NULL){
         right = (tree->right->value > tree->value);
      } 
      
      if(!(doIsBST(tree->left) && doIsBST(tree->right) && (left && right))){
         BST = FALSE;
      }
   }
   return BST;
}


int isBST(BSTree t){
   int isBSTLeft = FALSE;
   int isBSTRight = FALSE;
   int BST = FALSE;
   
   if(t != NULL){
      if(maxVal(t->left) < t->value && minVal(t->right) > t->value){
         isBSTLeft = doIsBST(t->left);
         isBSTRight = doIsBST(t->right);
         
         if(isBSTLeft && isBSTRight){
            BST = TRUE;
         }
         
      }      
   }
   return BST;
}



static BSTree doTrimTree(BSTree t, int level){
   if(t != NULL){
      if(level == 0){
         dropBSTree(t->left);
         t->left = NULL;
         dropBSTree(t->right);
         t->right = NULL;
      }else{
         t->left = doTrimTree(t->left, level-1);
         t->right = doTrimTree(t->right, level-1);
      }
   }
   return t;
}


BSTree trimTree(BSTree t, int level){
   Link returnVal = t;
   //
   
   if(level == 0){
      returnVal = NULL;
      dropBSTree(t);
      
   }else if( (treeHeight(t) < level) && (level != 0)){
      printf("Cannot trim tree to level %d, tree is not large enough", level);
   
   }else{
   
      returnVal = doTrimTree(t, level-1);
   }
   return returnVal;
}

int doIsBalanced(BSTree tree){
      int left = 0;
      int right = 0;
      int height = 0;
      
      if( tree != NULL){
      height = 1;
         if(tree->left != NULL){
            left = isBalanced(tree->left);
         }
         if(tree->right != NULL){
            right = isBalanced(tree->right);
         }
      }

   return left+right+height;
}

int isBalanced(BSTree t){
   int isBal = 1;
   int left;
   int right;
   
   left = doIsBalanced(t->left);
   right = doIsBalanced(t->right); 
   
   if(left != right){
      isBal = 0;
   }

   return isBal;   
}

int sumTree(BSTree t){
   int sum = 0;
   if(t != NULL ){
      int leftSum = 0;
      int rightSum = 0;
      
      leftSum = sumTree(t->left);
      rightSum = sumTree(t->right);
   
      sum = t-> value + leftSum + rightSum;
   }   

   return sum;
}








































