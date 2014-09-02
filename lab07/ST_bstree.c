#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Item.h"
#include "ST.h"

#define DEBUG

typedef struct STnode* link;
struct st{
    link root;
};

struct STnode { 
    Item item; 
    link left, right; 
    int size;
};

//static global variable - visible only in this file
static link emptyTree = NULL; //empty tree is the dummy node

static link NEW (Item item, link l, link r, int size){ 
    link newLink = malloc (sizeof *newLink);   
    newLink->item = item; 
    newLink->left = l; 
    newLink->right = r; 
    newLink->size = size;
    return newLink;
}

ST STinit () { 
    ST s = malloc(sizeof(struct st));
    if(emptyTree == NULL){
       emptyTree = NEW(NULLitem,NULL,NULL,0);
    }
    s->root = emptyTree;
    return s;
}

int STcount (ST s)  { 
    return s->root->size;
}

static Item searchR (link currentLink, Key searchKey) {
    if (currentLink == emptyTree) {
        return NULLitem;
    }
    Key currentKey = key(currentLink->item);
    if (eq(searchKey, currentKey)) {
        return currentLink->item;
    }
    if (less(searchKey, currentKey)) {
        return searchR (currentLink->left, searchKey);
    } else {
        return searchR (currentLink->right, searchKey);
    }
}

Item STsearch (ST s, Key searchKey) { 
    return searchR (s->root, searchKey); 
} 

//MODIFY THIS FUNCTION TO
//Update the size variable in the node
//Do not insert duplicates
static link insertR (link currentLink, Item item) { 

   if(currentLink == emptyTree){
      return NEW(item,emptyTree, emptyTree, 1 ); 
   
   }else if( !(eq(key(item), key(currentLink->item)){
      
      if(less( key(item),  key(currentLink->item))){
         currentLink->left = insertR(currentLink->left,item);
         
      }else if(greater( key(item),  key(currentLink->item))){
         currentLink->right = insertR(currentLink->right, item);
      }
      currentLink->size = currentLink->right->size+currentLink->left->size +1;
   }
   
   return currentLink;
}


void STinsert (ST s,Item item) { 
     //DO NOT MODIFY THIS FUNCTION
     s->root = insertR(s->root,item);
}

static Item selectR (link currentTree, int k) {
   if (currentTree == emptyTree) {
       return NULLitem;
   }
   if (currentTree->left->size == k) {
       return (currentTree->item);
   }
  
   if (currentTree->left->size > k) {
       return (selectR (currentTree->left, k));
   }

   return (selectR (currentTree->right, k - 1 - currentTree->left->size));
}

Item STselect (ST s,int k) {
   return (selectR (s->root, k));
}

//Need to remember to maintain size field
void STdelete (ST s,Item item){  
}

static void sortR (link currentLink, void (*visit)(Item)) { 
    if (currentLink == emptyTree) {
        return;
    }
    sortR (currentLink->left, visit);
    visit (currentLink->item); 
    sortR (currentLink->right, visit);
}

void STsort (ST s,void (*visit)(Item)) { 
    sortR (s->root, visit); 
} 

//FOR DEBUGGING PURPOSES
static
void doShowBSTree(link t, int level)
{
        int i;
        if (t == NULL) return;
        doShowBSTree(t->right, level+1);
        for (i = 0; i < level; i++) printf("   %d ",t->size);
        ITEMshow(t->item);       
        doShowBSTree(t->left, level+1);
}

void show(ST s)
{
        doShowBSTree(s->root, 0);
}

