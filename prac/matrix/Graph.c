// Ming Howard and Peter Kydd
//13/10/13 (i think)
// Graph.c for Lab wk 10
// no copyrights! woooooo

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "cities.h"
#include "Queue.h"

#define NO_EDGE -1

#define TRUE 1
#define FALSE 0

//#define DEBUG_1


struct GraphRep {
    int nV; // #vertices
    int nE[NUM_TRANSPORT]; //counter for number of edges of each type
    int connections[NUM_MAP_LOCATIONS][NUM_MAP_LOCATIONS];
};


static void makeMap(Graph g);
static void addLink(Graph g, Location start, Location end, Transport type);


Graph newGraph() {
    Graph g = malloc(sizeof(struct GraphRep));
    assert(g != NULL);
    g->nV = NUM_MAP_LOCATIONS;
    
    int rowCount;
    int colCount;
    
    //initialise matrix values to -1 to inidcate no connection
    for(rowCount = 0; rowCount < NUM_MAP_LOCATIONS; rowCount++){
        for(colCount = 0; colCount < NUM_MAP_LOCATIONS; colCount++){
            g->connections[rowCount][colCount] = NO_EDGE;
        }
    }
    
    
    g->nE[LAND] = 0;
    g->nE[SEA] = 0;
    makeMap(g);
    return g;
}

void destroyGraph(Graph g){
    assert(g != NULL);
    free(g);
}


static void addLink(Graph g, Location start, Location end, Transport type){
    assert (g != NULL);
    assert(type == SEA || type == LAND);
    
    g->connections[start][end] = type;
    g->connections[end][start] = type;
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
    
   #ifdef DEBUG_1
       printf("MAP MADE\n");
       printf("numSEA = %d\n", g->nE[SEA]);
       printf("numLAND = %d\n", g->nE[LAND]);
   #endif
}

//Useful for debugging
void showGraph(Graph g) {
    assert(g != NULL);
    printf("V=%d, E=%d + %d\n", g->nV, g->nE[LAND],g->nE[SEA]);
    int i,j;
    for (i = 0; i < g->nV; i++) {
        for(j = 0; j < g->nV; j++){
            if(isAdjacent(g,i,j,LAND)){
                printf("%d-%d L ",i,j);
            }
            if(isAdjacent(g,i,j,SEA)){
                printf("%d-%d S ",i,j);
            }
        }
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
    assert(g != NULL);
    assert(type == LAND || type == SEA || type == ANY || type == NO_EDGE);
    
    int isAdjacent = 0;
    
    if(g->connections[start][end] == LAND && type == LAND) {
        isAdjacent = 1;
    }else if (g->connections[start][end] == SEA && type == SEA){
        isAdjacent = 1;
    }else if((g->connections[start][end] == SEA || g->connections[start][end] == LAND) && (type == ANY) ){
        isAdjacent = 1;
    }
    
    return isAdjacent;
}

// Find the shortest path in the graph from the src to the destination using
// the given transport mode. The path array should be filled with a sequence of
// vertex numbers giving a path from src to dest.
// As this is an unweighted graph, the shortest path is simply the path with the least
// number of edges (least number of hops).
// It should return the size of the path or -1 if a path does not exits
// The path array is assumed to have enough space to hold the longest possible path (which
// would include all vertices).
int findShortestPath(Graph g,Location src, Location dest,Location path[],Transport type){
    assert(g != NULL);
    
    int hopCount = 0;
    
    // size of arrays is number of vertices minus 1, but add 1 for 0th element
    int preOrder[NUM_MAP_LOCATIONS] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int spanningTree[NUM_MAP_LOCATIONS] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    Queue queue = newQueue();
    Item tempEdge;
    
    int elementNum;
    int startVert;
    
    //assert(src.type == type);
    
    // spawn first edge for queue
    tempEdge.end = src;
    QueueJoin(queue, tempEdge);
    preOrder[src] = TRUE;
    
    // repeat until queue is empty
    while ( !QueueIsEmpty(queue) ) {
        
        // go through queue and find adj vertices for each of the vertices at the end of the edges
        startVert = QueueLeave(queue).end;
        
        // go through the adjacency matrix and...
        for (elementNum=0; elementNum<NUM_MAP_LOCATIONS; elementNum++) {
            
            // look at vertices adj to source (with the right type)
            if ((g->connections[startVert][elementNum] == type && preOrder[elementNum] == NO_EDGE) ||
                ((g->connections[startVert][elementNum] == LAND || g->connections[startVert][elementNum] == SEA) &&
                 preOrder[elementNum] == NO_EDGE && type == ANY)) {
                
                // go to each vertice's respective position in the spanning tree array, and enter in the src
                // (unless it has already been visited)
                spanningTree[elementNum] = startVert;
                
                // add these as edges to the queue
                tempEdge.start = startVert;
                tempEdge.end = elementNum;
                tempEdge.type = type;
                QueueJoin(queue, tempEdge);
                
                // record number of adj vertices found in pre[]
                preOrder[elementNum] = TRUE;
            }
            
        }
        
    }
    
    // clean up queue
    dropQueue(queue);
    
    int tempDest = dest;
    int currentLoc;
    int reversedPath[NUM_MAP_LOCATIONS];
    int i;
    
    //add the destination to the start of the list to print the entire path
    reversedPath[hopCount] = dest;
    hopCount++;
    // now retrieve the path from source to destination
    while (spanningTree[tempDest] != NO_EDGE) {
        currentLoc = spanningTree[tempDest];
        tempDest = currentLoc;
        reversedPath[hopCount] = currentLoc;
        hopCount++;
    }
    
    // if src is equal to dest
    if (src == dest) {
        path[0] = src;
        hopCount = 1;
        
    } else if (hopCount == 1) {
        hopCount = NO_EDGE;  // no shortest path
        //path[0] = src;
        
    } else {
        // reverse the path so it is from source to destination
        for (i=0; i<hopCount; i++) {
            path[i] = reversedPath[(hopCount-1)-i];
        }
    }
    
    // args 0 4 0
    //    0 1 2 3 4 5 6 7 8 9 10 11 12
    //st: 0 8 8 4 0 6 0 6 0 8 -1 -1 -1
    
   #ifdef DEBUG_1
       printf("\n");
       
       int printCount = 0;
       printf("element is:  ");
       while(printCount < NUM_MAP_LOCATIONS){
           printf("%2d ", printCount);
           printCount++;
       }
       printf("\n");
       printCount = 0;
       
       
       printf("preOrder is: ");
       while (printCount < NUM_MAP_LOCATIONS){
           
           printf("%2d ", preOrder[printCount]);
           printCount++;
       }
       printf("\n");
       
       printCount = 0;
       printf("spanTree is: ");
       while (printCount < NUM_MAP_LOCATIONS){
           
           printf("%2d ", spanningTree[printCount]);
           printCount++;
           
       }
       printf("\n");
   #endif
    
    
   #ifdef DEBUG_1
       printf("hopCount is: %d\n", hopCount);
   #endif
    
    return hopCount;
}
