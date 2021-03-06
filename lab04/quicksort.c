//peterKydd
//20/08/13
//quicksort with naive, medianthree, random pivot assignment


//#define DEBUG
#define DEBUG2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void quickSort(int a[], int l, int r);
void quickSortMT(int items[],int l, int r);
void quickSortRandom(int a[], int l, int r);
void swap(int index1, int index2, int items[]);
int partition(int a[], int l, int r);

int main(int argc, char *argv[]){
   
   //check argument strings 
   
   int naiveFlag = 0;
   int medianFlag = 0;
   int randomFlag = 0;
   int earlyExitFlag = 0;
    
   if((argc > 1)&&(strncmp(argv[1], "-pn", 3) == 0)){
      naiveFlag = 1;
      
   }else if((argc > 1)&& (strncmp(argv[1], "-pm", 3) == 0 )){
      medianFlag = 1;
       
   }else if((argc > 1)&&(strncmp(argv[1], "-pr", 3) == 0)){
      randomFlag = 1;  
   }
   if((argc>2)&&(strncmp(argv[2], "-q", 3) == 0 )){
      earlyExitFlag =1;
   }
   
   #ifdef DEBUG
      //printVals
      if(naiveFlag){
         printf("naive  pivot mode.\n");
      }else if(medianFlag){
         printf("median of three pivot mode.\n");
      }else if(randomFlag){
         printf("random pivot mode.\n");
      }else{
         printf("No sort selected, using standard quicksort. \n");
      }
      
      if(earlyExitFlag){
         printf("earlyExit activated.\n");
      }
   #endif 

    
   int size;
   int i;
   #ifdef DEBUG2
      printf("Enter data size: ");
   #endif
   scanf("%d",&size);

   int * a = malloc(size * sizeof(int));   
   #ifdef DEBUG2
      printf("Enter data: \n"); 
   #endif
   for(i=0;i<size;i++){
      scanf("%d",&a[i]);
   }
   
   if(naiveFlag){
      printf("Sorted with naive pivot:\n");
      quickSort(a,0,size-1);
   }else if(medianFlag){
      printf("Sorted with median of three pivot:\n");
      quickSortMT(a,0,size-1); 
   }else if(randomFlag){
      printf("Sorted with randomised pivot:\n");
      quickSortRandom(a,0,size-1);
   }else{
      printf("No sort selected, using standard quicksort. \n");
      quickSort(a,0,size-1);
   }
      

   if(!earlyExitFlag){
      
      //printf("Sorted\n");
      int printCount;
   
      for(printCount=0;printCount<size;printCount++){
         printf("%d ",a[printCount]);
      }
   }
   
   #ifdef DEBUG2
      printf("\n");
   #endif

   return 0;
}

void quickSort (int a[], int l, int r){         	
   int i;  
   if  (r <= l) {
      return;
   } 
   
   i = partition (a, l, r);  
   quickSort (a, l, i-1);  
   quickSort (a, i+1, r);
}


void quickSortRandom(int a[], int l, int r){
   int i; 
   int pivot; 
   srand (time(NULL));
   #ifdef DEBUG
      printf("left index %d\n",l ); 
      printf("right index %d\n",r ); 
   #endif
   
   if (r <= l) { 
      return;
   }

   pivot = l + rand()%(r-l+1);
   if(r-l > 1){
   #ifdef DEBUG
      printf("random index %d\n",pivot );
   #endif
      swap(r-1, pivot,a);

      if(a[r-1] < a[l]){ 
         swap(r-1,l,a);
      } 
      
      if(a[r] < a[l]){
         swap(r,l,a); 
      } if(a[r] < a[r-1]){
         swap(r,r-1,a);
      }

      i = partition(a,l+1,r-1);

   }else{ 
      i = partition(a,l,pivot);
   }
   #ifdef DEBUG
      printf("%d\n", pivot);
   #endif
   
   quickSortRandom (a, l, i-1);
   quickSortRandom (a, i+1, r);
}

void quickSortMT(int a[], int l, int r){         	
   int i;  
   if  (r <= l) {
      return;
   } 
   if(r-l > 1){
      int mid = (r+l)/2;

      swap(r-1,mid,a);
      if(a[r-1] < a[l]){
        swap(r-1,l,a);
      }
      if(a[r] < a[l]){
        swap(r,l,a);
      }
      if(a[r] < a[r-1]){
        swap(r,r-1,a);
      }
  
      i = partition(a,l+1,r-1);
   } else {
      i = partition(a,l,r);  
   }  
 
   quickSortMT (a, l, i-1);  
   quickSortMT (a, i+1, r);
}


//PARTITION 
int partition (int a[], int l, int r) {   
   int i = l-1;
   int j = r;   
   int pivot = a[r]; //rightmost is pivot  	
   for(;;) {   
	   while ( a[++i] < pivot) ;    
	   while ( pivot <  a[--j] && j != l);
	   if (i >= j) { 
         break;
      }    
	   swap(i,j,a);  
   }
    //put pivot into place  
   swap(i,r,a);  
    return i; //Index of the pivot
}

//SWAP VARIABLES
void swap(int index1, int index2, int items[]){
    int tmp;
    tmp = items[index1];
    items[index1] = items[index2];
    items[index2] = tmp;
}




