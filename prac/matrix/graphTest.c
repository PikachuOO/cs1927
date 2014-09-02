#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cities.h"
#include "Graph.h"


void showIsAdjacent(Graph g);
void showShortestPaths(Graph g,Location src, Location dest, Transport type);
void usage();  
void fatal(char *);


int main(int argc, char * argv[]){
    
    Graph g;
    g = newGraph();    
    if(argc == 1){
        showGraph(g);
        assert(numV(g) == NUM_MAP_LOCATIONS);
        assert(numE(g,LAND) == 17);
        assert(numE(g, SEA) == 8);
        
        showIsAdjacent(g);
        
    } else if(argc == 4){

        int src,dest,type;
        sscanf(argv[1],"%d",&src);
        sscanf(argv[2],"%d",&dest);
        sscanf(argv[3],"%d",&type);
        showShortestPaths(g,src,dest,type);

    } else {
        usage();
    }
    destroyGraph(g);
    return 0;
}

//Prints out adjacency information for all
//pairs of vertices for all connection types
//Can be used for debugging
void showIsAdjacent(Graph g){
    int i,j;
    printf("Sea connections\n");
    for(i=0; i < NUM_MAP_LOCATIONS; i++){
        for(j=0; j < NUM_MAP_LOCATIONS; j++){
            printf("%d ",isAdjacent(g,i,j,SEA));
        }
        printf("\n");
    }
    printf("LAND connections\n");
    for(i=0; i < NUM_MAP_LOCATIONS; i++){
        for(j=0; j < NUM_MAP_LOCATIONS; j++){
            printf("%d ",isAdjacent(g,i,j,LAND));
        }
        printf("\n");
    }
    printf("ANY connections\n");
    for(i=0; i < NUM_MAP_LOCATIONS; i++){
        for(j=0; j < NUM_MAP_LOCATIONS; j++){
            printf("%d ",isAdjacent(g,i,j,ANY));
        }
        printf("\n");
    }

}

void showShortestPaths(Graph g, Location src, Location dest, Transport type){
       char * types[] = { "land","sea","any"};
       assert(src  >= 0  && src  <= numV(g));
       assert(dest >= 0  && dest <= numV(g));
       assert(type >= 0  && type <= ANY);

       printf("Shortest path from %d to %d with travel type %s\n",src,dest,types[type]);
       Location locations[NUM_MAP_LOCATIONS];
       int size = findShortestPath(g, src, dest, locations,type);
       if(size == -1){
           printf("No Path found\n");
       } else {
           int i;
           for(i=0 ; i< size; i++){
               printf("%d ",locations[i]);
           }
           printf("\n");
       }
}

// print usage message and stop
void usage()
{
        fprintf(stderr, "Usage: [Start-city Destination-city Transport-type]\n");
        exit(1);
}

// print message for unrecoverable error and stop
void fatal(char *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

