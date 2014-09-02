//29/09/13
//code suppplied ?
//Modified by Winwood Callum Ming Jiang Howard and Peter Kydd.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "cities.h"

#define DEBUG_PRINT_LIST

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
static VList newNode (Location newLocation, Transport newType);
static void doCanReachInN(Graph g, Location start, Transport type, int n, int locs[]);

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
            //should we really be freeing current??? 
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


static VList newNode (Location newLocation, Transport newType) {
    VList new = malloc( sizeof(struct vNode) );
    
    assert(new != NULL);
    
    new->v = newLocation;
    new->type = newType;
    new->next = NULL;
    
    return new;
}

static void makeMap(Graph g){
    
    //RULE BRITTANIA!
    addLink(g, LONDON, SWANSEA, RAIL);
    addLink(g, LONDON, SWANSEA, LAND );
    addLink(g, LONDON, PLYMOUTH, LAND );
    addLink(g, LONDON, MANCHESTER, LAND );
    addLink(g, LONDON, MANCHESTER, RAIL );
    addLink(g, LONDON, ENGLISH_CHANNEL, SEA);
    addLink(g, LIVERPOOL, SWANSEA, LAND );
    addLink(g, LIVERPOOL, IRISH_SEA, SEA);
    
    addLink(g, MANCHESTER, EDINBURGH, LAND);
    addLink(g, MANCHESTER, EDINBURGH, RAIL);
    addLink(g, MANCHESTER, LIVERPOOL, LAND);
    addLink(g, MANCHESTER, LIVERPOOL, RAIL);
    addLink(g, GALWAY, DUBLIN, LAND);
    addLink(g, GALWAY, ATLANTIC-OCEAN, SEA);
    
    addLink(g, DUBLIN, IRISH_SEA, SEA);
    addLink(g, PLYMOUTH, ENGLISH_CHANNEL, SEA);
    addLink(g, EDINBURGH, NORTH_SEA, SEA);
    
       
    //OTHER COUNTRIES, AKA, PEASANT FILTH
        
    //OCEAN LINKS
    addLink(g, ATLANTIC_OCEAN, NORTH_SEA, SEA);
    addLink(g, NORTH_SEA, ENGLISH_CHANNEL, SEA);
    addLink(g, BAY_OF_BISCAY, ATLANTIC_OCEAN, SEA);
    addLink(g, ATLANTIC_OCEAN, MEDITERRANEAN_SEA, SEA);
    addLink(g, ATLANTIC_OCEAN, MEDITERRANEAN_SEA, SEA);
    addLink(g, MEDITERRANEAN_SEA, TYRR,);
    addLink(g, , ,);
    addLink(g, , ,);
    addLink(g, , ,);
    addLink(g, , ,);


    
    addLink(g, LE_HAVRE, ENGLISH_CHANNEL, SEA);
    addLink(g, AMSTERDAM, NORTH_SEA, SEA);
    addLink(g, HAMBURG, NORTH_SEA, SEA);
    addLink(g, NANTES, BAY_OF_BISCAY, SEA);
    addLink(g, BORDEAUX, BAY_OF_BISCAY, SEA);
    
    //SPAIN LINKS
    addLink(g, SANTANDER, BAY_OF_BISCAY, SEA);
    addLink(g, LISBON, ATLANTIC_OCEAN, SEA );
    addLink(g, CADIZ, ATLANTIC_OCEAN, SEA );
    addLink(g, MADRID, SANTANDER, LAND );
    addLink(g, MADRID, SANTANDER, RAIL );
    addLink(g, MADRID, LISBON, LAND );
    addLink(g, MADRID, LISBON, RAIL );
    addLink(g, MADRID, CADIZ, LAND );
    addLink(g, MADRID, GRANADA, LAND );
    addLink(g, LISBON, CADIZ, LAND );
    addLink(g, CADIZ, GRANADA, LAND );
    addLink(g, GRANADA, ALICANTE, LAND );
    addLink(g, MADRID, ALICANTE, LAND );
    addLink(g, MADRID, ALICANTE, RAIL );
    addLink(g, ALICANTE, BARCELONA, RAIL );
    addLink(g, BARCELONA, TOULOUSE, LAND );
    addLink(g, SARAGOSSA, BARCELONA, RAIL,);
    addLink(g, SARAGOSSA, ALICANTE, LAND );
    addLink(g, SARAGOSSA, ALICANTE, RAIL );
    addLink(g, MADRID, SARAGOSSA, LAND );
    addLink(g, SANTANDER, LISBON, LAND );
    addLink(g, SARAGOSSA, BORDEAUX, LAND );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    addLink(g, , , );
    
    
    
    
    
    
    
    
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
            printf("[%d][type %d]->", current->v, current->type);
            //
            
            current = current->next;
        }
        
        printf("[X]\n");
        listCount++;
    }
}
