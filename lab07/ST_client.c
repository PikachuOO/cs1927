#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

//This program reads in items representing
//student id, names and inserts them into a 
//a symbol table
int main (int argc, char *argv[]) { 

  Item currIt;
  int n;
  int counter;
  ST s = STinit ();
  
  counter = 0;
  while (ITEMscan (&currIt)) {
        STinsert (s,currIt);     
        counter++;
  }
  
  printf("Read in %d items\n",counter);
  n = STcount(s);
  printf("There are %d items in the symbol table\n",n);  

  printf("The data sorted by key:\n");
  STsort (s,&ITEMshow);

  printf("The item with the smallest key is ");
  ITEMshow(STselect(s,0)); 

  printf("The item with the median key is ");
  ITEMshow(STselect(s,n/2));


  printf("The item with the largest key is ");  
  ITEMshow(STselect(s,n - 1));


  return EXIT_SUCCESS;
}
