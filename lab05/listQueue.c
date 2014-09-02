//peterkydd
//27/13/13
//listQueue.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queue.h"

typedef struct queueNode * link;

struct queueNode { 
    Item item; 
    link next; 
};

struct queueImp { 
    link head; 
    link tail;
    int size; 
};

static link createNode(Item item){ 
    link n = malloc (sizeof(*n));
    assert(n != NULL);
    n->item = item; 
    n->next = NULL;     
    return n;                         
}

// Creates an empty Queue
Queue createQueue (void){ 
    Queue q = malloc (sizeof (*q));
    assert(q != NULL); 
    q->head = NULL; 
    q->tail = NULL;
    q->size = 0; 
    return q;
}
//destroys queue
void destroyQueue(Queue queue){
    link curr;
    link next;
    assert(queue != NULL);
    curr = queue->head;
    
    while(curr !=NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }
    queue = NULL;
    free(queue); 
}

int queueSize (Queue q){ 
    assert(q != NULL);
    return q->size; 
}

void putQueue (Queue q, Item item){ 
    assert(q != NULL); 
    link n = createNode(item);
    q->size++;
    
    if(q->tail != NULL){  //check to see that tail is not null 
       q->tail->next = n;
       q->tail = n;
       
    } else {
       q->tail = n; 
       q->head = n;
    }
}

//get item data from head of queue and delete that node. 
Item getQueue (Queue q){ 
    assert(q != NULL);
    if(q->size > 0){
        Item item = q->head->item;
        link delNode = q->head;
        q->head = q->head->next;      
        free(delNode);
        q->size--;
        return item;
    } else {
        fprintf(stderr,"queue underflow\n");
        abort();          
    }
}
