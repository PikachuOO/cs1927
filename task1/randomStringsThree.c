// peter kydd
// 12/08/13
// string generator

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomPermutation(int length, int stringNum);

int main (int argc, char *argv[]){

   int length = atoi(argv[1]); 
   int stringNum = atoi(argv[2]); 
   
   randomPermutation(length, stringNum);
   return EXIT_SUCCESS;
}

void randomPermutation(int length, int stringNum){

   int wordCount;
   int printCount;
   char randChar;

   srand(time(NULL));
   
   for(wordCount = 0; wordCount < stringNum; wordCount++){
      for(printCount  = 0; printCount< length; printCount++){
         if(wordCount % 7 == 0){
            randChar = 'Z';
         }else if(wordCount % 3 == 0){
            randChar = 'A';
         }else{
            randChar = ((rand() % 52) + 65);
              
            if((randChar > 'Z') && (randChar < 'a')){
               randChar = randChar+7;
            }
         }
         printf("%c", randChar);
         
      }
      printf("\n");
   }
}
