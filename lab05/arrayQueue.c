//peterkydd
//27/13/13
//arrayQueue.c

#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"
#include <assert.h>

#define DEFAULT_SIZE 100

struct queueImp{
    Item *items;
    int size;
    int end;
    int start;
    int maxSize;
};

//O(1)
Queue createQueue(){
    Queue q = malloc(sizeof(struct queueImp));
    q->items = malloc(DEFAULT_SIZE * sizeof(Item));
    q->size =0;
    q->start = 0;
    q->end = 0;
    q->maxSize = DEFAULT_SIZE;
    return q;
}

void destroyQueue(Queue q){
    assert(q != NULL);
    free(q->items);
    free(q);
}

//O(1)
int queueSize(Queue q){
    assert(q != NULL);
    return (q->size);
}

//O(1)
void putQueue(Queue q, Item i){
    assert(q != NULL);
    
    
    if(q->end < q->maxSize){
        q->items[(q->end)]  = i;
    } else {
        fprintf(stderr,"queue overflow\n");
        abort();
    }
    
    q->end++;
    q->size = (q->end)-(q->start); 
}

//O(1) 
Item getQueue(Queue q){
    assert(q != NULL);
    if(!(q->size >=1)){
       abort();
    }
    
    Item item = q->items[(q->start)];
    q->start++;
    q->size = (q->end)-(q->start); 
    
    if(q->size == 0){
       q->start = 0;
       q->end = 0;
    }
    
    return item;
     
}
