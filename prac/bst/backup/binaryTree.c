//binary tree implementation 
//peter kydd
//26/10


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "binaryTree.h"

typedef struct _treeRep{
   TreeNode root;
   int size;
} treeRep;


typedef struct _treeNodeRep{
   int data;
   int size;
   TreeNode left;
   TreeNode right;
} treeNodeRep;


// creates a new node and returns poitner to that node 
static TreeNode newTreeNode(int data){
   TreeNode newNode = malloc(sizeof(struct _treeNodeRep));
   assert(newNode != NULL);
   newNode->left = NULL;
   newNode->right = NULL;
   newNode->data = data;
   
   return newNode;
}

// find the node containing the specified value
// return NULL if value not found;
// for use with delete node etc. 
static TreeNode findValue(Tree t){
   
   printf("NEED TO IMPLEMENT FINDVALUE.\n");
   
   return t->root;
}

static void doDisposeTree(TreeNode node){
   
   if( node->left != NULL){
      doDisposeTree(node->left);
      free(node->left);
   
   }
   if(node->right != NULL){
      doDisposeTree(node->right);
      free(node->right);
   
   }
}

// dispose of tree and free malloc'd memory 
void disposeTree(Tree t){
   
   if(t->root != NULL){
      doDisposeTree(t->root);
   }
   
   free(t);

}


Tree createTree(void){
   Tree newTree = malloc(sizeof(treeRep));
   assert(newTree != NULL);
   
   newTree->root = NULL;
   newTree->size = 1;
   
   return newTree;

}

void insertAtRoot(Tree t, TreeNode newNode){
   assert(t != NULL);
   newNode->left = t->root;
   t->root = newNode->left;
   
   t->size++;
}


static void doInsertOrdered(TreeNode n, TreeNode newNode){
   assert(n != NULL && newNode != NULL);
   
   if(newNode->data < n->data){
      if(n->left == NULL){
         n->left = newNode;
      }else{
         doInsertOrdered(n->left, newNode); 
      }
   }else if(newNode->data > n->data){
      if(n->right == NULL){
         n->right = newNode;
      }else{
         doInsertOrdered(n->right, newNode);
      }
   }
   
}

// inserts a new node at a balanced position in the tree
void insertOrdered(Tree t, TreeNode newNode){
   assert(t != NULL);

   doInsertOrdered(t->root, newNode);
   
   t->size++;
}


 void doDeleteNode(TreeNode n, int key){
    if(n == NULL){
       
       // traverse left
       if(key < n->left->data){
          doDeleteNode(n->left, key);
       
       // traverse right
       } else if(key > n->right->data){
          doDeleteNode(n->right, key);
       
       // we have found the node to delete   
       }else if(key == n->left->data){
          // node has no children
          // we can free it
          if(n->left->left == NULL && n->left->right == NULL){
             free(n->left);
             n->left = NULL;
             
          // node has 1 child on the right
          // 'link past' the node, then free it.
          }else if(n->left->left == NULL && n->left->right != NULL){
             TreeNode temp;
             temp = n->left->right;
             n->left->right = NULL;
             free(n->left);
             n->left = temp;
          
          // node has 1 child on the left
          // 'link past' the node, then free it.
          }else if(n->left->left != NULL && n->left->right == NULL)){
            TreeNode temp;
            temp = n->left->left;
            n->left->left = NULL;
            free(n->left);
            n->left = temp;
          
          //deal with the case where the node has multiple children
          }else if(n->left->left != NULL && n->left->right != NULL){
             
             // find leftern most element of right subtree
             // this will be reversed for deleting the right subtree
             int temp
             TreeNode current;
             for(current = n->left->right; current->left != NULL; current = current->left){
             }
             //put that lefternmost element into node to be deleted
             temp = current->left->data;
             free(current->left);
             current->left = NULL;
             
             //place value into node
             n->left->data = temp;
             
          }          
       }else if(key == n->right->data)
          // node has no children
          // we can free it
          if(n->right->left == NULL && n->right->right == NULL){
             free(n->right);
             n->right = NULL;
          } 
          // node has 1 child on the right
          // 'link past' the node, then free it.
          }else if(n->right->right == NULL && n->right->left != NULL){
             TreeNode temp;
             temp = n->right->left;
             n->right->left = NULL;
             free(n->right);
             n->right = temp;
          
          // node has 1 child on the left
          // 'link past' the node, then free it.
          }else if(n->right->right != NULL && n->right->left == NULL)){
            TreeNode temp;
            temp = n->right->right;
            n->right->right = NULL;
            free(n->right);
            n->right = temp;
          
          //deal with the case where the node has multiple children
          }else if(n->right->right != NULL && n->right->left != NULL){
             
             // find right most element of left subtree
             // this will be reversed for deleting the left subtree
             int temp
             TreeNode current;
             for(current = n->right->left; current->right != NULL; current = current->right){
             }
             //put that lefternmost element into node to be deleted
             temp = current->right->data;
             free(current->right);
             current->right = NULL;
             
             //place value into node
             n->right->data = temp;
       
       }
    }
 }

//delete the node with the specified value
// if value is not discovered, print error message
void deleteNode(Tree t, int key){
   assert(t != NULL);
   
   doDeleteNode(t->root, key);
}

// checks to see if the tree is degenerate 
int isDegenerate(Tree t);

// prints postFix order (L R N)
void printPostFix(Tree t);
   
// prints in inFix order (L N R)
void printInFix(Tree t);

// prints in preFix order (N L R)
void printPreFix(Tree t);

// checks to see if a value is in the tree (ie, search for value)
int inTree(Tree t);

// draw the tree in a tree-like way  
void drawTree(Tree t);

// return the height of the tree
int getHeight(Tree t);

// trim the tree below a certain level
void trimTree(Tree t, int depth);




