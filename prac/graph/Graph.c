#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"
#include "Graph.h"
#include "cities.h"


typedef struct vNode *VList;

struct vNode { 
    Location v;     //ALICANTE etc
    Transport type; //LAND, SEA, ANY
    VList next; 
};  

struct GraphRep { 
    int nV; // #vertices
    int nE[NUM_TRANSPORT]; //counter for number of edges of each type    
    VList connections[NUM_MAP_LOCATIONS]; // array of lists 
}; 


static void makeMap(Graph g);
static void addLink(Graph g, Location start, Location end, Transport type);

static VList newNode (Location newLocation, Transport newType) {
    VList new = malloc( sizeof(struct vNode) );
    
    assert(new != NULL);
    
    new->v = newLocation;
    new->type = newType;
    new->next = NULL;
    
    return new;
}

Graph newGraph() { 
    int i; 
    Graph g = malloc(sizeof(struct GraphRep));
    assert(g != NULL);
    g->nV = NUM_MAP_LOCATIONS;
    for (i = 0; i < g->nV; i++){ 
        g->connections[i] = NULL;  
    }
     
    g->nE[LAND] = 0;
    g->nE[SEA] = 0; 
    makeMap(g);
    return g; 
} 

void destroyGraph(Graph g){
    int i;
    VList curr;
    VList next;
    assert(g != NULL);
    assert(g->connections != NULL);
  
    for (i = 0; i < g->nV; i++){         
         curr = g->connections[i];
         while(curr !=NULL){
             next = curr->next;
             free(curr);
             curr=next;
         }
    }
    free(g);
}   


static void addLink(Graph g, Location start, Location end, Transport type){
    //assert that g is not NULL
    assert(g != NULL);
    
    // this handles the start list (necessary duplicate entry)
    VList current = g->connections[start];
    VList new = newNode(end, type);
    assert(new != NULL);
    
    if (g->connections[start] == NULL) {
        g->connections[start] = new;
        
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = new;
    }
    
    current = g->connections[end];
    
    //we forgot to do this. you can get rid of all the extra stuff now, this fixes all of those problems.
    new = newNode(start, type);
    
    if (g->connections[end] == NULL) {
        g->connections[end] = new;
        
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = new;
    }
    
    //increment link count
    g->nE[type]++;
}


static void makeMap(Graph g){
   addLink(g, ALICANTE, GRANADA, LAND);
   addLink(g, ALICANTE, MADRID, LAND);
   addLink(g, ALICANTE, SARAGOSSA, LAND);
   addLink(g, BARCELONA, SARAGOSSA, LAND);
   addLink(g, BARCELONA, TOULOUSE, LAND);  
   addLink(g, BORDEAUX, SARAGOSSA, LAND);
   addLink(g, BORDEAUX, TOULOUSE, LAND); 
   addLink(g, CADIZ, GRANADA, LAND);
   addLink(g, CADIZ, LISBON, LAND);
   addLink(g, CADIZ, MADRID, LAND);
   addLink(g, GRANADA, MADRID, LAND);
   addLink(g, LISBON, MADRID, LAND);
   addLink(g, LISBON, SANTANDER, LAND);
   addLink(g, MADRID, SANTANDER, LAND);
   addLink(g, MADRID, SARAGOSSA, LAND); 
   addLink(g, SANTANDER, SARAGOSSA, LAND);
   addLink(g, SARAGOSSA, TOULOUSE, LAND); 
  
   addLink(g, ALICANTE, MEDITERRANEAN_SEA, SEA); 
   addLink(g, ATLANTIC_OCEAN, BAY_OF_BISCAY, SEA);
   addLink(g, ATLANTIC_OCEAN, CADIZ, SEA);
   addLink(g, ATLANTIC_OCEAN, LISBON, SEA);
   addLink(g, ATLANTIC_OCEAN, MEDITERRANEAN_SEA, SEA);
   addLink(g, BARCELONA, MEDITERRANEAN_SEA, SEA); 
   addLink(g, BAY_OF_BISCAY, BORDEAUX, SEA);
   addLink(g, BAY_OF_BISCAY, SANTANDER, SEA);
}

//Useful for debugging
void showGraph(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d + %d\n", g->nV, g->nE[LAND],g->nE[SEA]); 
    int i; 
    for (i = 0; i < g->nV; i++) { 
        VList n = g->connections[i]; 
        while (n != NULL) { 
            printf("%d-%d ",i,n->v); 
            if(n->type == LAND){
                printf("L ");
            } else if(n->type == SEA){
                printf("S ");
            } else {
                printf("ERROR NO SUCH TYPE");
                exit(0);
            }
            n = n->next; 
        } 
        if (g->connections [i] != NULL) 
            printf("\n"); 
        } 
} 

int numV(Graph g){
    assert(g != NULL);
    return g->nV;
}

int numE(Graph g, Transport type){
    assert(g != NULL);
    assert(type >= 0 && type <= ANY);
    if(type == ANY){
        return g->nE[LAND] + g->nE[SEA];
    } else {
        return g->nE[type];
    }
}

//returns 1 if there is an edge from start to end of the given type
//gives 0 otherwise
int isAdjacent(Graph g,Location start, Location end, Transport type){
    int adjacent = 0;
    VList current = g->connections[start];
    
    while (current != NULL) {
        
        if (current->v == end && current->type == type) {
            adjacent = 1; // true
        } else if (current->v == end && type == ANY) {
            adjacent = 1;
        }
        current = current->next;
    }
    
    return adjacent;
}



static void doCanReachInN(Graph g, Location start, Transport type, int n, int locs[]){
   
   if(n>=0){ //make sure that target is in step radius of start
      
      
      
      if((g->connections[start]->type == type) || (type == ANY)){
         VList current = g->connections[start];
         
         locs[start] = 1;
         
         while(current != NULL){
            doCanReachInN(g, current->v, type, n-1, locs);
            current = current->next;
         }
         
      }else{
         VList current = g->connections[start];
         
         while(current != NULL){
            if((current->type == type)){
               locs[start] = 1;
               doCanReachInN(g, current->v, type, n-1, locs);
               
            }
            current = current->next;
         }
      }
   }
}


//Determines which locations can be reached from the start location
//in n hops or less with a given transport type
//If a location can be reached in n hops or less locs[location] is set to 1
//otherwise it is left as 0
void canReachInN(Graph g, Location start, Transport type, int n, int locs[]){
   assert(g != NULL);
   
   locs[start] = 1;
   
   doCanReachInN(g, start, type, n, locs);

}

void printList(Graph g){
    int listCount = 0;
    
    VList current = g->connections[listCount];
    
    while(listCount < NUM_MAP_LOCATIONS){
        
        current = g->connections[listCount];
        printf("Printing: g->connections[%d]->", listCount);
        
        while(current != NULL){
            //printf("[%d][type %d]->", current->v, current->type);
            //
            printf("[%d]->", current->v);

            
            current = current->next;
        }
        
        printf("[X]\n");
        listCount++;
    }
}

void bfs(Graph g, Location start){
   assert(g != NULL);
   
   int location;
   int count;
   int pre[g->nV];
   int st[g->nV];
   
   //initialise values for st and pre arrays
   for(count = 0; count < g->nV; count++){
      pre[count] = -1;
      st[count] = -1;
   } 
   
   Queue q = newQueue();
   QueueJoin(q, start);
   VList current;
   count = 0;
   
   while(!QueueIsEmpty(q)){
      showQueue(q);
      location = QueueLeave(q); 
      printf("enQueueing %d\n", location);
      
      for(current = g->connections[location]; current != NULL; current = current->next){

         if(pre[current->v] == -1){
            QueueJoin(q, current->v);
            st[current->v] = location;
            pre[current->v] = count;
            printf("updating st...\n");
         }
         count++;
      } 
   }
   
   // printing for debug   
   for(count = 0; count < g->nV; count++){
      printf("pre[%d] = %d\n", count, pre[count]);
      printf("st[%d] = %d\n", count, st[count]);
   } 
   
}

static void doDfs(Graph g, Location location, int *pre, int* st, int depthCount){
   assert(g != NULL);
   
   depthCount++;
   pre[location] = depthCount;
   VList current = g->connections[location];
   
   //printf("%d\n",current->v);
   
   while(current != NULL){
      if(pre[current->v] == -1){
         doDfs(g, current->v, pre, st, depthCount);
         st[current->v] = location;
      }
      
      current = current->next;
   }
}


void dfs(Graph g, Location start){
   assert(g != NULL);
   
   int count;
   int innerCount = 0;
   int pre[g->nV];
   int st[g->nV];
   
   for(count = 0; count < g->nV; count++){
      pre[count] = -1;
      st[count] = -1;
   }
     
   doDfs(g, start, pre, st, count); 
   
   count = 0;
   while(count < NUM_MAP_LOCATIONS){
      
      printf("path from %d is:\n", start);
      printf("START->");
   
      if(count != start){
         innerCount = count;
         while(st[innerCount] != -1){
            printf("%d->", st[innerCount]);
            innerCount = st[innerCount];
            
         }
         
      }
      printf("X\n");
      count++;
   }
   
   
   //   printing st array
   
   for(count = 0; count < g->nV; count++){
      //printf("pre[%d] = %d\n", count, pre[count]);
      printf("st[%d] = %d\n", count, st[count]);
   } 
   
}

int getDegree(Graph g, int target){
   assert(g != NULL);
   int numDirections = 0;
   
   int count;
   VList current;
   
   for(count = 0; count < g->nV; count++){
          
      for(current = g->connections[count]; current != NULL; current = current->next){ 
         // count != target to simulate directed nature of graph. 
         if((current->v == target) && (count != target)){
            numDirections++;
         }
      }
   }  
      
   return numDirections;
}

