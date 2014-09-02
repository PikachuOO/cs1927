#ifndef GRAPH_H
#define GRAPH_H

#include "cities.h"

#define LAND 0
#define SEA 1
#define RAIL 2
#define ANY 3
#define NUM_TRANSPORT 3  // <-- hours of my life I will never get back

#define SURPR_EMPTY 0
#define SURPR_VAMP 1
#define SURPR_TRAP 2


// vertices denoted by integers 0..N-1
typedef int Location;
typedef int Transport;

typedef struct path {
    Location start;
    Location end;
    Transport type;
} Path;

// graph representation is hidden
typedef struct GraphRep *Graph;

typedef struct locNode *locList;

struct locNode {
    int location;     // ALICANTE etc
    int type; // LAND, SEA, ANY
    locList next;
};

struct GraphRep {
    int numVertices; // #vertices
    int numPaths[NUM_TRANSPORT]; //counter for number of edges of each type
    locList connections[NUM_LOCATIONS]; // array of lists
};

// operations on graphs
Graph newGraph();
void destroyGraph(Graph g);
void showGraph(Graph g);

int numVertices(Graph g);
int numPaths(Graph g, Transport t);

//create the map node connections
void makeMap(Graph g);


//returns 1 if there is an edge from start to end with a given transport type
//returns 0 otherwise
int isAdjacent(Graph g,Location start, Location end, Transport type);

//Determines which locations can be reached from the start location
//in n hops or less with a given transport type
//If a location can be reached in n hops or less locs[location] is set to 1
void canReachInN(Graph g, Location start, Transport type, int n, int locs[]);

void printList(Graph g);

#endif
