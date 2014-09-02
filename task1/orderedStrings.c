// peter kydd
// 12/08/13
// string generator

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void orderedPermutation(int length, int stringNum);

int main (int argc, char *argv[]){

   int length = atoi(argv[1]); 
   int stringNum = atoi(argv[2]); 
   
   orderedPermutation(length, stringNum);
   return EXIT_SUCCESS;
}

void orderedPermutation(int length, int stringNum){

   int wordCount;
   int printCount;
   
   char character;
   
   srand(time(NULL));
   
   for(wordCount = 0; wordCount < stringNum; wordCount++){
      for(printCount  = 0; printCount< length; printCount++){
         character;
         
         
         printf("%c", character);
         
      }
      printf("\n");
   }
}
