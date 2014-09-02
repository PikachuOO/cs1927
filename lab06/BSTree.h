// BSTree.h ... interface to binary search tree ADT
// Written by John Shepherd, March 2013

#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTNode *BSTree;

// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);
// display a BSTree (sideways)
void showBSTree(BSTree);

// print values in infix order
void BSTreeInfix(BSTree t);
// print values in prefix order
void BSTreePrefix(BSTree t);
// print values in postfix order
void BSTreePostfix(BSTree t);
// print values in level-order
void BSTreeLevelOrder(BSTree t);

// count #nodes in BSTree
int BSTreeNumNodes(BSTree);
// count #leaves in BSTree
int BSTreeNumLeaves(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, int);
// check whether a value is in a BSTree
int BSTreeFind(BSTree, int);

#endif
