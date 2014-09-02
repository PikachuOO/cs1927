#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

/* read from stdin */
int ITEMscan (Item *item) {
  Item it = malloc (sizeof (*it));
  *item = it;
  if ((scanf ("%d", &(it->keyval)) == 1) &&
      (scanf ("%9s", (it->value)) == 1)) {
    return 1;
  } else {
    return 0;
  }
}  
void ITEMshow (Item item){
    if(item != NULLitem)
        printf ("%d \t %s \n", item->keyval, item->value);
    else
        printf("NO ITEM \n");
}
