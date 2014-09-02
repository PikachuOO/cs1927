//peterKydd
//19/08/13
// a program to generate ordered data

#define DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main (int argc, char *argv[]){

   //check argument strings
   
   int naiveFlag = 0;
   int medianFlag = 0;
   int randomFlag = 0;
   int earlyExitFlag = 0;
   
   
   if(strncmp(argv[1], "-pn", 3) == 0){
      naiveFlag = 1;
      
   }else if( strncmp(argv[1], "-pm", 3) == 0 ){
      medianFlag = 1;
       
   }else if(strncmp(argv[1], "-pr", 3) == 0){
      randomFlag = 1;  
   }
   if((argc>2)&&(strncmp(argv[2], "-q", 3) == 0 )){
      earlyExitFlag =1;
   }
   
   //printVals
   if(naiveFlag){
      printf("naiveFLag = 1\n");
   }else if(medianFlag){
      printf("medianFLag = 1\n");
   }else if(randomFlag){
      printf("randomFlag = 1\n");
   }
   
   if(earlyExitFlag){
      printf("earlyExitFLag = 1\n");
   }
   
   return EXIT_SUCCESS;
}
