//peterKydd
//12/08/13
//simple Analysis of strings

//#define DEBUG
//#define DEBUG2

#define STRING_LENGTH  36

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main (int argc, char *argv[]){
   
   #ifdef DEBUG2
      printf("\n");
   #endif
   
   //ENSURE THAT THE INPUT FILE IS VALID
   if(argv[1] == NULL){
      printf("Error Reading input File;\n");
      assert(argv[1] != NULL);
   }
   
   //READ NUMBER OF LINES IN FILE TO ALLOCATE DYNAMIC ARRAY
   FILE *pFile = fopen(argv[1], "r");
   
   char nlChar;
   unsigned int lineCount = 0;
   
   while((nlChar = fgetc(pFile)) != EOF){
      if(nlChar == '\n'){
         lineCount++;
      }
   }
   
   #ifdef DEBUG
      printf("lineCount is: %d\n", lineCount);
   #endif
   
   
   //CREATE ARRAYS DYNAMICALLY
   
   //MASTER ARRAY
   char **seqMaster = malloc(lineCount*(sizeof(char*)));//create first dimension of 2d array
   int arrayCount = 0;
   
   while(arrayCount<lineCount){
      seqMaster[arrayCount] = malloc((STRING_LENGTH+3)*(sizeof(char)));//create 2nd dimension
      memset(seqMaster[arrayCount], 0, (STRING_LENGTH+3)*(sizeof(char)));//initialise the array 
      arrayCount++;
   }
  
   //DUPLICATE ARRAY
   char **seqDuplicate = malloc(lineCount*(sizeof(char*)));
   char **dupeMult = malloc(lineCount*(sizeof(char*)));
   
   arrayCount = 0;
   
   while(arrayCount<lineCount){
      seqDuplicate[arrayCount] = malloc((STRING_LENGTH+3)*(sizeof(char)));
      memset(seqDuplicate[arrayCount], 0, (STRING_LENGTH+3)*(sizeof(char)));
      arrayCount++;
   }
   
   arrayCount = 0;
   
   while(arrayCount<lineCount){
      dupeMult[arrayCount] = malloc((STRING_LENGTH+3)*(sizeof(char)));
      memset(dupeMult[arrayCount], 0, (STRING_LENGTH+3)*(sizeof(char)));
      arrayCount++;
   }
   
   //MAX CONSECUTIVE ARRAY
   char **seqMaxConsec = malloc(lineCount*(sizeof(char*)));
   arrayCount = 0;
   
   while(arrayCount<lineCount){
      seqMaxConsec[arrayCount] = malloc((STRING_LENGTH+3)*(sizeof(char)));
      memset(seqMaxConsec[arrayCount], 0, (STRING_LENGTH+3)*(sizeof(char)));
      arrayCount++;
   }
              
   //MIN CONSECUTIVE ARRAY
   char **seqMinConsec = malloc((lineCount)*(sizeof(char*)));
   arrayCount = 0;

   while(arrayCount<lineCount){
      seqMinConsec[arrayCount] = malloc((STRING_LENGTH+1)*(sizeof(char)));
      memset(seqMinConsec[arrayCount], 0, (STRING_LENGTH+1)*(sizeof(char)));
      arrayCount++;
   }
   
   //POPULATE MASTER ARRAY WITH DATA FROM FILE
   
   arrayCount = 0;
   pFile = fopen ( argv[1], "r");
   
   while(arrayCount < lineCount){ 
      fgets(seqMaster[arrayCount], (STRING_LENGTH+2), pFile);
      seqMaster[arrayCount][STRING_LENGTH] = 0;
      arrayCount++;
   }
      
   fclose (pFile);
   
   
   //POPULATE DUPLICATE ARRAY//
   unsigned int compReturn = -99;
   unsigned int dupeA = 0;
   unsigned int dupeB = 0;
   unsigned int dupeCounter = 0;
   unsigned int dupeCheck = 0;
   unsigned int dupeCheckCount = 0;
   unsigned int dupeFlag = 0;
   
   //compares seqMaster[dupeA] --->>> seqMaster[dupeB]
   while(dupeA < lineCount){
      dupeB = 0;
      
      while(dupeB < lineCount){
         dupeCheckCount = 0;
         dupeFlag = 0;
         compReturn = strncmp(seqMaster[dupeA], seqMaster[dupeB], (STRING_LENGTH));
       
         //if duplicate is found, this will copy it into the duplicate array
         //UNLESS: it is already present in the array/comparing to itself (dupeA == dupeB)
         if((compReturn == 0) && (dupeA != dupeB)){
            strncpy(seqDuplicate[dupeCounter], seqMaster[dupeB], (STRING_LENGTH) );
            dupeCounter++;
            
            //this loop looks for duplicates in the duplicates array (ugh)
            while(dupeCheckCount<dupeCounter){
               dupeCheck = strncmp(seqMaster[dupeB], dupeMult[dupeCheckCount], (STRING_LENGTH));
               dupeCheckCount++;
           
               //flags duplicates in duplicate array so that they are not copied twice
               if(dupeCheck==0){
                  dupeFlag = 1;
               }   
            }         
           
            //if duplicate of duplicate is not present in dupe array, copies string over
            if(dupeFlag !=1){
               strncpy(dupeMult[dupeCounter], seqMaster[dupeB], (STRING_LENGTH) );
               dupeCounter++;
            }
         }
         dupeCheck = 0;
         dupeB++;
      }
      dupeA++;
   }
   
   #ifdef DEBUG
      printf("Number of duplicates was: %d\n", dupeCounter);
   #endif
   
  
    
   //POPULATE MAX CONSECUTIVE ARRAY
   
   int maxConsec = 0;
   unsigned int consecPos = 0;
   unsigned int consecCounter = 0;
   unsigned int consecCounterTemp = 0;
   unsigned int consecA = 0;
   unsigned int consecB = 0;
   unsigned int consecBTemp = 0;
   
   dupeCheck = 0;
   dupeCheckCount = 0;
   dupeFlag = 0;
   
   while(consecA < lineCount){
      consecB = 0;
      consecCounter = 0;
      
      //PARSE seqMaster[consecA] string for consecutive letters
      while(seqMaster[consecA][consecB+1] != 0){
         consecBTemp = consecB;
         
         while(seqMaster[consecA][consecBTemp] == seqMaster[consecA][consecBTemp+1]){
            consecCounterTemp++;
            consecBTemp++;
         }
         consecBTemp = 0;
        
         if(consecCounterTemp> consecCounter){
           consecCounter = consecCounterTemp;
         }
        
         consecCounterTemp = 0;
         consecB++;
      }
      
      #ifdef DEBUG
      //   printf("current string = %s\n", seqMaster[consecA], consecCounter);
      #endif
      
      if(consecCounter > maxConsec){
         consecPos = 0;
         maxConsec = consecCounter;
         
         //in case of NEW MAX, wipes all old values
         arrayCount = 0;
         while(arrayCount<lineCount){
            memset(seqMaxConsec[arrayCount], 0, (STRING_LENGTH)*(sizeof(char)));
            arrayCount++;
         }
         strncpy(seqMaxConsec[consecPos], seqMaster[consecA], (STRING_LENGTH) );
         consecPos++;
        
      }else if(consecCounter == maxConsec){
         
         //CHECK FOR DUPLICATES
         while(dupeCheckCount < lineCount){
            dupeCheck = strncmp(seqMaster[consecA], seqMaxConsec[dupeCheckCount], STRING_LENGTH);
            dupeCheckCount++;
            
            if(dupeCheck==0){
               dupeFlag = 1;
            }
         }
         
         if(dupeFlag != 1){
            strncpy(seqMaxConsec[consecPos], seqMaster[consecA], (STRING_LENGTH) );
            consecPos++;
         }       
      }
      dupeCheckCount = 0;
      dupeFlag = 0;
      consecA++;  
   }
   #ifdef DEBUG   
      printf("Number of MAX consecutives was: %d\n", consecPos);
   #endif
   
   
   //POPULATE MIN CONSECUTIVE ARRAY
   
   int minConsec = 99999999;
   consecPos = 0;
   consecCounter = 0;
   consecCounterTemp = 0;
   consecA = 0;
   consecB = 0;
   consecBTemp = 0;
   dupeCheckCount = 0;
   dupeCheck = 0;
   dupeFlag = 0;
   
   while(consecA < lineCount){
      consecB = 0;
      consecCounter = 0;
      
      //PARSE seqMaster[consecA] string for consecutive letters
      while(seqMaster[consecA][consecB+1] != 0){
         consecBTemp = consecB;
         while(seqMaster[consecA][consecBTemp] == seqMaster[consecA][consecBTemp+1]){
            consecCounterTemp++;
            consecBTemp++;
         }
         consecBTemp = 0;
        
         if(consecCounterTemp> consecCounter){
           consecCounter = consecCounterTemp;
         }
        
         consecCounterTemp = 0;
         consecB++;
      }
      
      #ifdef DEBUG
         printf("%s had %d consecutive letters\n", seqMaster[consecA], consecCounter);
      #endif
      
      if((consecCounter < minConsec) && consecCounter > 0 ){
         
         consecPos = 0;
         minConsec = consecCounter;
         
         //in case of NEW MIN, wipes all old values
         arrayCount = 0;
         while(arrayCount<lineCount){
            memset(seqMinConsec[arrayCount], 0, (STRING_LENGTH+1)*(sizeof(char)));
            arrayCount++;
         }
                                
         strncpy(seqMinConsec[consecPos], seqMaster[consecA], (STRING_LENGTH+2) );
         consecPos++;
      
      }else if(consecCounter == minConsec){
         
         while(dupeCheckCount < lineCount){
            dupeCheck = strncmp(seqMaster[consecA], seqMinConsec[dupeCheckCount], STRING_LENGTH);
            dupeCheckCount++;
            
            if(dupeCheck==0){
               dupeFlag = 1;
            }
         }
            
            if(dupeFlag != 1){
               strncpy(seqMinConsec[consecPos], seqMaster[consecA], (STRING_LENGTH) );
               consecPos++;
            }       
            
      }
      dupeCheckCount = 0;
      dupeFlag = 0;
      consecA++;       
   }
   
   #ifdef DEBUG   
      printf("Number of MIN consecutives was: %d\n", consecPos);
   #endif
 
 
   
   //SORT ARRAYS
   
   //SORT DUPLICATES
   int countA = 0;
   int countB = 0;
   char stringTemp[100] = {'\0'};
   memset(stringTemp, 0, 100);
   int orderCheck = 0;
   
   while (countA < lineCount){
        
      countB = 0;      
      while (countB < (lineCount-1)){
         orderCheck = strcmp(seqDuplicate[countB], seqDuplicate[countB+1]);
         //printf("ordercheck is %d\n", orderCheck);
         
         if (orderCheck > 0){
             strncpy(stringTemp, seqDuplicate[countB], STRING_LENGTH*(sizeof(char)));
             strncpy(seqDuplicate[countB], seqDuplicate[countB+1], STRING_LENGTH*(sizeof(char)));
             strncpy(seqDuplicate[countB+1], stringTemp, STRING_LENGTH*(sizeof(char)));   
          }
          countB++;
      }
      countA++;
    }
    
   //SORT DUPLICATES MULTIPLES
   countA = 0;
   countB = 0;
   
   memset(stringTemp, 0, 100);
   orderCheck = 0;
   
   while (countA < lineCount){
        
      countB = 0;      
      while (countB < (lineCount-1)){
         orderCheck = strcmp(dupeMult[countB], dupeMult[countB+1]);
         //printf("ordercheck is %d\n", orderCheck);
         
         if (orderCheck > 0){
             strncpy(stringTemp, dupeMult[countB], STRING_LENGTH*(sizeof(char)));
             strncpy(dupeMult[countB], dupeMult[countB+1], STRING_LENGTH*(sizeof(char)));
             strncpy(dupeMult[countB+1], stringTemp, STRING_LENGTH*(sizeof(char)));   
          }
          countB++;
      }
      countA++;
    }

   //SORT MAX CONSEC
   countA = 0;
   countB = 0;
   memset(stringTemp, 0, 100);
   orderCheck = 0;
   
   while (countA < lineCount){
        
      countB = 0;      
      while (countB < (lineCount-1)){
         orderCheck = strcmp(seqMaxConsec[countB], seqMaxConsec[countB+1]);
         //printf("ordercheck is %d\n", orderCheck);
         
         if (orderCheck > 0){
             strncpy(stringTemp, seqMaxConsec[countB], STRING_LENGTH*(sizeof(char)));
             strncpy(seqMaxConsec[countB], seqMaxConsec[countB+1], STRING_LENGTH*(sizeof(char)));
             strncpy(seqMaxConsec[countB+1], stringTemp, STRING_LENGTH*(sizeof(char)));   
          }
          countB++;
      }
      countA++;
    }
    
   //SORT MIN CONSEC
   

   countA = 0;
   countB = 0;
   memset(stringTemp, 0, 100);  
   orderCheck = 0;

   while (countA < lineCount){
        
      countB = 0;      
      while (countB < (lineCount-1)){
         orderCheck = strcmp(seqMinConsec[countB], seqMinConsec[countB+1]);
         //printf("ordercheck is %d\n", orderCheck);
         
         if (orderCheck > 0){
             strncpy(stringTemp, seqMinConsec[countB], (STRING_LENGTH+1)*(sizeof(char)));
             strncpy(seqMinConsec[countB], seqMinConsec[countB+1], (STRING_LENGTH+1)*(sizeof(char)));
             strncpy(seqMinConsec[countB+1], stringTemp, (STRING_LENGTH+1)*(sizeof(char)));   
          }
          countB++;
      }
      countA++;
   }
  
   //PRINT LISTS
   
   int printCount = 0;
   //MAXCONSEC
   printf("Sequence(s) with the most consecutive repeated bases:\n");
   while(printCount< lineCount){
      if(seqMaxConsec[printCount][0] > 40){ 
         printf("* %s\n",  seqMaxConsec[printCount]);
         
      }
      printCount++;
   }
   printf("\n");
   
     
   //MINCONSEC
   printCount = 0;
   printf("Sequence(s) with the least consecutive repeated bases:\n");
   while(printCount < lineCount){
      if(seqMinConsec[printCount][0] > 40){
         printf("* %s\n",  seqMinConsec[printCount]);
         
      }
      printCount++;
   }
   printf("\n");

   printCount = 0;
   
   //CHECK DUPLICATE MULTIPLICITY
   printf("Duplicate sequences:\n");
   int duplicateCount = 0;
   countA = 0;
   countB = 0;
   
   //scan thru DUPEMULT for individual strings
   while(countA < lineCount){
      countB = 0;
      duplicateCount = 0;
      
      //look for multiples in SEQDUPLICATE
      while(countB < lineCount){
         
         if(!strncmp(seqDuplicate[countB],  dupeMult[countA], STRING_LENGTH )){
            duplicateCount++;
         }
         countB++;
      }
      
      if(dupeMult[countA][0] > 40){
         //printf("Duplicate ocurred: %2d times. String was: %s\n", duplicateCount, dupeMult[countA] );
         printf("%2d %s\n", duplicateCount, dupeMult[countA]);
      }
      
      countA++;   
   }
   printf("\n");
   
   return EXIT_SUCCESS;
}


