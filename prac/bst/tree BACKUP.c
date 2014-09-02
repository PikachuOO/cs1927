
static int max(int a, int b){
   int returnVal = a;
   
   if(a<b){
      returnVal = b;
   }
   
   return returnVal;
}

static int treeHeight(BSTree t){
   int returnVal = 1;
   int heightLeft = 0;
   int heightRight = 0;
   
   if(t == NULL){
      returnVal = 0;
   }else{
      if (t->left != NULL){
         heightLeft = treeHeight(t->left);
      }
      if(t->right != NULL){
         heightRight = treeHeight(t->right);      
      }
   }
   return (returnVal + max( heightLeft, heightRight ));
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

