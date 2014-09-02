//peterkydd
//27/13/13
// Queue.h 
typedef int Item;
typedef struct queueImp *Queue;
 
//Function Prototypes 
Queue createQueue( void ); 
void destroyQueue( Queue queue ); 
Item getQueue( Queue queue); 
void putQueue( Queue queue, Item data); 
int queueSize( Queue queue); 


