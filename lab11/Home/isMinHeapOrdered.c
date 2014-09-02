
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "isMinHeapOrdered.h"
//To compile, run and test
//gcc -Wall -Werror -O -o testIsMinHeapOrdered testIsMinHeapOrdered.c isMinHeapOrdered.c


//returns 1 if the tree-based heap is in min-heap order.
//You may assume an empty tree is in min-heap order and so 
//is a single node.
int isMinHeapOrdered(Link n){
	int isOrdered = 1;

	if(n != NULL && (n->left != NULL )){

   printf("n->item = %d\n", n->item);
   printf("n->LEFT->item = %d\n", n->left->item);

		if(n->left->item < n->item){
			isOrdered = 0;
		}else{
			isOrdered = isMinHeapOrdered(n->left);
		}

		if((n->right != NULL && isOrdered == 1)){
		
		printf("n->RIGHT->item = %d\n", n->right->item);
		
			if(n->right->item < n->item){
				isOrdered = 0;
			}else{
				isOrdered = isMinHeapOrdered(n->right);
			}

		}
	}

    return isOrdered;
}


