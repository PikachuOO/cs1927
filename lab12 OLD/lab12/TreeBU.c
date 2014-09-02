//An implementation of a BST with a field (size) to 
//keep how many nodes are in each sub-tree
//This implementation also includes functions to balance the tree


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Item.h"
#include "Tree.h"

//This is how many levels of the tree the TREEdisplay will print out
#define MAXLEVEL 15
#define IMBAL_REFERENCE 50

typedef struct node * link;

struct treeImp{
    link root;
    int balanceStrategy;
};

struct node{
    Item item;
    link left;
    link right;
    int size; //Keeps track of the number of nodes in each sub-tree
};

static link emptyTree = NULL;


// Local function prototypes
static link NEW (Item item, link l, link r, int size);
static int max(int a, int b);
static void destroyNodes(link n);


//search functions
static int searchR(link  t, Key k);
link searchSplay (link n, Key k, int * found);

//insert functions

static link insert(link currentLink, Item item);
static link insertAtRoot(link currentLink, Item item);
link insertRandom(link currentLink, Item item);
link insertSplay (link tree, Item item);

//balancing functions
static link rotLeft (link currentTree);
static link rotRight (link currentTree);
link balance(link tree);
static link partitionR (link currentTree, int pos);

//display and info functions
static int recursiveHeight(link n);
static void dump(link n, int level, int maxLevel);

static link NEW (Item item, link l, link r, int size){ 
    link newLink = malloc (sizeof *newLink); 
  
    newLink->item = item; 
    newLink->left = l; 
    newLink->right = r; 
    newLink->size = size;
    return newLink;
}

//Initialises a tree
//In this implementation, a tree is not just a pointer to the root node
//but is a struct which contains a pointer to the root node.
Tree TREEinit(int balanceStrategy){
    Tree t = malloc(sizeof(struct treeImp));
    assert(t!= NULL);
    if(emptyTree == NULL){
      emptyTree = NEW(NULLitem,NULL,NULL,0);
    }
    t->root = emptyTree;
    t->balanceStrategy = balanceStrategy;
    if(t->balanceStrategy == RANDOMISED){
        srand(time(NULL)); //seed random number generator for insertRandom
    } 
    return t;
}

//returns the size of the tree
int TREEcount(Tree tree){
    if(tree->root == NULL) return 0;
    return tree->root->size;
}


//YOU NEED TO MODIFY THIS FOR TASK 1
//A function that inserts an item into a binary tree and 
//balances the tree, depending on the defined rebalance strategy
//We will assume we do not care about duplicates for this
void TREEinsert(Tree tree, Item it){
   assert(tree!= NULL);
   if(tree->balanceStrategy == NO_REBALANCE){
      tree->root =  insert(tree->root,it);
        
     //balance at each entry
   }else if(tree->balanceStrategy == REBALANCE_1){
      tree->root = insert(tree->root,it);
      tree->root = balance(tree->root);
         
   //balance every 100 entries
   }else if(tree->balanceStrategy == REBALANCE_100){
      tree->root = insert(tree->root,it);
      
      if(tree->root->size % 100 == 0){
         tree->root = balance(tree->root); 
      }
   
   //balance every 1000 entries 
   }else if(tree->balanceStrategy == REBALANCE_1000){
      tree->root = insert(tree->root,it);
      
      if(tree->root->size % 1000 == 0){
         tree->root = balance(tree->root); 
      }
      
   //randomised balanced insertion
   }else if(tree->balanceStrategy == RANDOMISED){
      tree->root = insertRandom(tree->root,it);
            
   //splay balanced insert
   }else if(tree->balanceStrategy == SPLAY){
      tree->root = insertSplay(tree->root,it);
   
   //my balancing strategy
   }else{
      //printf("NEED TO IMPLEMENT MY OWN STRAT...\n");
      tree->root = insert(tree->root,it);
      
      Tree left = malloc(sizeof(struct treeImp));
      left->root = tree->root->left;
      
      Tree right = malloc(sizeof(struct treeImp));
      right->root = tree->root->right;
      
      int leftHeight = TREEheight(left);
      int rightHeight = TREEheight(right);
      
      if(abs(leftHeight - rightHeight)>IMBAL_REFERENCE){
         tree->root = balance(tree->root);
      }
      //exit(1);
   }
   
}


//You must change this for task 2
//Uses normal search or splay search, depending on
// the balance strategy
int TREEsearch(Tree t, Key k){
    int result;
    assert(t != NULL);
    
    if( t->balanceStrategy == SPLAY ){
       searchSplay(t->root, k, &result);
       //printf("Searching SPLAY\n");
       
    } else {
       result =  searchR(t->root,k);
       //printf("Searching OTHER\n");
       
    }
    
    return result;
}

//Finds the height of the tree
int TREEheight(Tree t){
    assert(t != NULL);
    return recursiveHeight(t->root);
}

void TREEdestroy(Tree t){
    assert(t != NULL);
    destroyNodes(t->root);
    free(emptyTree);
    free(t);
}

void TREEdisplay(Tree t){
    assert(t != NULL);
    dump(t->root,0,MAXLEVEL);
}

//Prints out some statistics about the tree
void TREEshowStats(Tree t){
    if(t->balanceStrategy == NO_REBALANCE){
        printf("No Rebalance Strategy\n");
    }else if(t->balanceStrategy == REBALANCE_1){
        printf("Global Rebalance Strategy 1\n");
    }else if(t->balanceStrategy == REBALANCE_100){
        printf("Global Rebalance Strategy 100\n");
    }else if(t->balanceStrategy == REBALANCE_1000){
        printf("Global Rebalance Strategy 1000\n");
    }else if(t->balanceStrategy == RANDOMISED){
        printf("Randomised Insertion\n");
    }else if(t->balanceStrategy == SPLAY){
        printf("Splay  \n");
    }else if(t->balanceStrategy == MY_REBALANCE){
        printf("My balance  \n");
    }else{
        printf("Unknown rebalance strategy\n");
        exit(0);
    }
    printf("#nodes = %d, height = %d\n",TREEcount(t), TREEheight(t));
}


// A local helper function to find the max of two integers
static int max(int a, int b){
   int result;
   if (a >=b) {
       result =  a;
   }else{
       result =  b;
   }
   return result;
}

// Finds the height of a tree with root n
static int recursiveHeight(link n){
    int result = -1;
    if(n != emptyTree){
        result =  1 + max(recursiveHeight(n->left),
                          recursiveHeight(n->right)); 
    }
    return result;
}

// A recursive version of standard BST insertion
// Modified to update the size counters
link insert (link currentLink, Item item) { 
  
   if (currentLink == emptyTree) {
       return (NEW (item, emptyTree, emptyTree, 1));
   }
   if (less (key (item), key (currentLink->item))) {
       currentLink->left = insert (currentLink->left, item);
   } else if (less (key (currentLink->item), key (item))) {
       currentLink->right = insert (currentLink->right, item);
   }
   currentLink->size++;
   return (currentLink);
}

// A recursive function that inserts the new item 
// at the root of the tree. This is used in randomInsert
link insertAtRoot(link currentLink, Item item){
    if(currentLink == emptyTree){
        return (NEW(item,emptyTree,emptyTree,1));
    } 
    //size gets updated by the rotate functions
    if (less (key (item), key (currentLink->item))) {
        currentLink->left = insertAtRoot (currentLink->left, item);
        currentLink = rotRight(currentLink);
    } else {
        currentLink->right = insertAtRoot (currentLink->right, item);
        currentLink = rotLeft(currentLink);
    } 
  
    return (currentLink);
  
}

// Randomly inserts either at the leaf of the tree or the root
link insertRandom(link currentLink, Item item){
 
  if (currentLink == emptyTree) {
    return (NEW (item, emptyTree, emptyTree, 1));
  }
  //Prob 1/N
  if(rand() < RAND_MAX/(currentLink->size+1)){
    return insertAtRoot(currentLink,item);
  } else if (less (key (item), key (currentLink->item))) {
    currentLink->left = insertRandom (currentLink->left, item);
  } else {
    currentLink->right = insertRandom (currentLink->right, item);
  } 
  currentLink->size++;
  return (currentLink);
}



// Performs a standard recursive search for the key in the given tree
// returns 1 if found and 0 otherwise
int searchR(link  t, Key k){
    int returnVal;
    if (t == NULL || t == emptyTree){
        returnVal =  0;
    }else if (less(k,t->item)){
	returnVal =  searchR(t->left, k);
    }else if (greater(k,t->item)){
	returnVal =  searchR(t->right, k);
    }else{
        returnVal =  1;
    }
    return returnVal;
}

static link rotLeft (link currentTree) {
    link rotLTree = currentTree->right;
    currentTree->right = rotLTree->left;
    rotLTree->left = currentTree;
    rotLTree->left->size = rotLTree->left->left->size + rotLTree->left->right->size +1;
    rotLTree->size = rotLTree->left->size + rotLTree->right->size + 1;
   
    return rotLTree;
}

static link rotRight (link currentTree) {
    link rotRTree = currentTree->left;
    currentTree->left = rotRTree->right;
    rotRTree->right = currentTree;
    rotRTree->right->size = rotRTree->right->left->size + rotRTree->right->right->size + 1;
    rotRTree->size = rotRTree->right->size+ rotRTree->left->size+1;

    return rotRTree;
}



// partition tree at node with position pos (counting from 0) in the
// sorted sequence of all items, node become new root node.
// Will only work once as rotRight and rotLeft do not 
// update size fields properly
link partitionR (link currentTree, int pos) {
    int leftSubtreeSize = currentTree->left->size;
    if (leftSubtreeSize > pos) {
        currentTree->left = partitionR (currentTree->left, pos);
        currentTree = rotRight (currentTree) ;
    } else if (leftSubtreeSize < pos) {
        currentTree->right = 
        partitionR (currentTree->right, pos - 1 - leftSubtreeSize);
        currentTree = rotLeft (currentTree) ;    
    }
    return currentTree;
}

link balance(link tree){
    if(tree->size >=2){
        tree = partitionR(tree,tree->size/2);
        tree->left = balance(tree->left);
        tree->right = balance(tree->right);
    }
    return tree;
}

link insertSplay (link tree, Item item) {
    Key v = key (item);
    if (tree == emptyTree)
        return (NEW (item, emptyTree, emptyTree, 1)); 
  
    if (less (v, key(tree->item))) {
        if (tree->left == emptyTree) {
            return (NEW (item, emptyTree, tree, tree->size+1));
        }
        if (less (v, key (tree->left->item))) {
            tree->left->left = insertSplay (tree->left->left, item);
            tree = rotRight (tree); 
        } else {
            tree->left->right = insertSplay (tree->left->right, item);
            tree->left = rotLeft (tree->left);
        }
            return rotRight (tree);
    } else {
        if (tree->right == emptyTree) {
            return (NEW (item, tree, emptyTree, tree->size+1));
        }
        if (less (key (tree->right->item), v)) {
            tree->right->right = insertSplay (tree->right->right, item);
            tree = rotLeft (tree);
        } else {
            tree->right->left = insertSplay (tree->right->left, item);
            tree->right = rotRight (tree->right);
        }
        return rotLeft (tree);
     }
}

link searchSplay (link n, Key k, int * found){
    link returnVal = NULL;
    *found = 0;

    //root does not exist
    if (n == NULL) {
        *found = 0;
        returnVal = n;
    }

    //root = key
    else if (eq(key(n->item),k)) {
        *found = 1;
        returnVal = n;
    }

    //key is less than root
    else if ( less(k,key(n->item)) ) {
        if ( eq(key(n->left->item),k) ) {
            *found = 1;
            returnVal = rotRight(n);
        }

        if ( less(k,key(n->left->item)) ) {
            n->left->left = searchSplay(n->left->left,k,found);
            n = rotRight(n);
        }

        else if ( greater(k,key(n->left->item)) ) {
            n->left->right = searchSplay(n->left->right,k,found);
            n->left = rotLeft(n->left);
        }

    }

    //key is greater than root
    else if ( greater (k, key(n->item) ) ) {
        if ( eq(key(n->right->item),k) ) {
            *found = 1;
            returnVal = rotLeft(n);
        }

        if ( less(k,key(n->right->item)) ) {
            n->right->right = searchSplay(n->right->right,k,found);
            n = rotLeft(n);
        }

        else if ( greater(k,key(n->left->item)) ) {
            n->right->left = searchSplay(n->right->left,k,found);
            n->right = rotRight(n->right);
        }
    }

    return returnVal;

}

static void destroyNodes(link n){
    if( n != emptyTree){
        destroyNodes(n->left);
        destroyNodes(n->right);
        free(n->item);
        free(n);
    }
}

// Prints out a tree
// Handles recursion and level maintenance
static void dump(link n, int level, int maxLevel){
    if (n == NULL || n == emptyTree){
        printf("X\n");
    } else if (level == maxLevel){
        printf("...\n");
    }else {
        int i;
        showItem(n->item);
        printf(" (%d) ",n->size);
        printf("\n"); 
        if (n->left != NULL) {
            for (i = 0; i < level; i++){
                printf("|  ");
            }
            printf("|--L: ");
            dump(n->left, level+1, maxLevel);
        }
        if (n->right != NULL) {
            for (i = 0; i < level; i++){
                printf("|  ");
            }
            printf("|--R: ");
            dump(n->right, level+1, maxLevel);
        }
    }
}
