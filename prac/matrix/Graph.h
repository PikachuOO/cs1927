#ifndef GRAPH_H
#define GRAPH_H

#define LAND 0
#define SEA 1
#define ANY 2
#define NUM_TRANSPORT 2


// vertices denoted by integers 0..N-1 
typedef int Location;
typedef int Transport; 

typedef struct edge{
    Location start;
    Location end;
    Transport type;
} Edge;

// graph representation is hidden 
typedef struct GraphRep *Graph; 

// operations on graphs 
Graph newGraph();  
void destroyGraph(Graph g); 
void showGraph(Graph g); 

int numV(Graph g);
int numE(Graph g, Transport t);


//returns 1 if there is an edge from start to end with a given transport type
//returns 0 otherwise
int isAdjacent(Graph g,Location start, Location end, Transport type);


int findShortestPath(Graph g,Location src, Location dest,Location path[],Transport type);

#endif
