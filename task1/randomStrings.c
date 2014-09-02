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
   
   //int letterCount = 0;
   //int custPermFlag = 0;
   
   char randChar;
   //char letterRead;
   //char custPerm[10000] = {'#'};
   /*
   while(((letterRead = getchar()) != EOF) && ((letterRead != '\n'))){
      custPerm[letterCount] = letterRead;
      letterCount++;
   }
   
   if(letterCount > 0){
      custPermFlag = 1;
   }
   */
   //printf("\n");
   srand(time(NULL));
   
   for(wordCount = 0; wordCount < stringNum; wordCount++){
      for(printCount  = 0; printCount< length; printCount++){
         /*
         if(custPermFlag){        
            randChar = custPerm[((rand() % letterCount))];
         
         }else{
         */
            randChar = ((rand() % 52) + 65);
              
            if((randChar > 'Z') && (randChar < 'a')){
               randChar = randChar+7;
            }
         //}
         printf("%c", randChar);
         
      }
      printf("\n");
   }
}
