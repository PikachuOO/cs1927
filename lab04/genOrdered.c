//peterKydd
//19/08/13
// a program to generate ordered data

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
     int size = 10;
     int i;
     if(argc > 1){
       size = atoi(argv[1]);
     }

     printf("%d\n",size);
     for(i =0; i < size; i++){
          printf("%d\n",i);
     }
     return 0;
}

