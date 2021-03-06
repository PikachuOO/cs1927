// Modified by Callum Howard and Peter Kydd for 1927 lab09
// 29th September 2013.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "cities.h"

//#define DEBUG_PRINT_LIST


static void addLink(Graph g, Location start, Location end, Transport type);
static locList newNode (Location newLocation, Transport newType);

Graph newGraph() {
    int i;
    Graph g = malloc(sizeof(struct GraphRep));
    assert(g != NULL);
    g->numVertices = NUM_MAP_LOCATIONS;
    for (i = 0; i < NUM_MAP_LOCATIONS; i++){
        g->connections[i] = NULL;
    }
    
    g->numPaths[LAND] = 0;
    g->numPaths[SEA] = 0;
    makeMap(g);
    return g;
}

void destroyGraph(Graph g){
    int i;
    locList curr;
    locList next;
    assert(g != NULL);
    assert(g->connections != NULL);
    
    for (i = 0; i < g->numVertices; i++){
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
    locList current = g->connections[start];
    locList new = newNode(end, type);
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
    g->numPaths[type]++;
}


static locList newNode (Location newLocation, Transport newType) {
    locList new = malloc( sizeof(struct locNode) );
    
    assert(new != NULL);
    
    new->location = newLocation;
    new->type = newType;
    new->next = NULL;
    
    return new;
}

void makeMap(Graph g){
    
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
    addLink(g, GALWAY, ATLANTIC_OCEAN, SEA);
    
    addLink(g, DUBLIN, IRISH_SEA, SEA);
    addLink(g, PLYMOUTH, ENGLISH_CHANNEL, SEA);
    addLink(g, EDINBURGH, NORTH_SEA, SEA);
    
    //IST ICH EIN BERLINER!
    addLink(g, STRASBOURG, PARIS, LAND );
    addLink(g, STRASBOURG, BRUSSELS, LAND );
    addLink(g, STRASBOURG, GENEVA, LAND );
    addLink(g, STRASBOURG, ZURICH, RAIL );
    addLink(g, STRASBOURG, ZURICH, LAND );
    addLink(g, STRASBOURG, NUREMBURG, LAND );
    addLink(g, STRASBOURG, MUNICH, LAND );
    addLink(g, COLOGNE, AMSTERDAM, LAND );
    addLink(g, COLOGNE, BRUSSELS, LAND );
    addLink(g, COLOGNE, BRUSSELS, RAIL );
    addLink(g, COLOGNE, STRASBOURG, LAND );
    addLink(g, COLOGNE, FRANKFURT, LAND );
    addLink(g, COLOGNE, FRANKFURT, RAIL );
    addLink(g, COLOGNE, HAMBURG, LAND );
    addLink(g, COLOGNE, LEIPZIG, LAND );
    addLink(g, STRASBOURG, FRANKFURT, LAND );
    addLink(g, STRASBOURG, FRANKFURT, RAIL );
    addLink(g, FRANKFURT, NUREMBURG, LAND );
    addLink(g, FRANKFURT, LEIPZIG, LAND );
    addLink(g, FRANKFURT, LEIPZIG, RAIL );
    addLink(g, HAMBURG, LEIPZIG, LAND );
    addLink(g, HAMBURG, BERLIN, RAIL );
    addLink(g, HAMBURG, BERLIN, LAND );
    addLink(g, BERLIN, LEIPZIG, LAND );
    addLink(g, BERLIN, LEIPZIG, RAIL );
    addLink(g, BERLIN, PRAGUE, LAND );
    addLink(g, BERLIN, PRAGUE, RAIL );
    addLink(g, LEIPZIG, NUREMBURG, LAND );
    addLink(g, LEIPZIG, NUREMBURG, RAIL );
    addLink(g, NUREMBURG, MUNICH, LAND );
    addLink(g, NUREMBURG, MUNICH, RAIL );
    addLink(g, ZURICH, MUNICH, LAND );
    addLink(g, MUNICH, MILAN, LAND );
    addLink(g, MUNICH, VENICE, LAND );
    addLink(g, NUREMBURG, PRAGUE, LAND );
    addLink(g, MUNICH, VIENNA, LAND );
    addLink(g, VIENNA, VENICE, RAIL );
    addLink(g, MUNICH, ZAGREB, LAND );
    
    
    //OCEAN LINKS
    addLink(g, ATLANTIC_OCEAN, NORTH_SEA, SEA);
    addLink(g, NORTH_SEA, ENGLISH_CHANNEL, SEA);
    addLink(g, BAY_OF_BISCAY, ATLANTIC_OCEAN, SEA);
    addLink(g, ATLANTIC_OCEAN, MEDITERRANEAN_SEA, SEA);
    
    addLink(g, IRISH_SEA, ATLANTIC_OCEAN, SEA);
    addLink(g, ATLANTIC_OCEAN, ENGLISH_CHANNEL, SEA);
    
    addLink(g, MEDITERRANEAN_SEA, TYRRHENIAN_SEA, SEA );
    addLink(g, TYRRHENIAN_SEA, IONIAN_SEA, SEA);
    addLink(g, IONIAN_SEA, ADRIATIC_SEA, SEA);
    addLink(g, IONIAN_SEA, BLACK_SEA, SEA);
    addLink(g, LE_HAVRE, ENGLISH_CHANNEL, SEA);
    addLink(g, AMSTERDAM, NORTH_SEA, SEA);
    addLink(g, HAMBURG, NORTH_SEA, SEA);
    addLink(g, NANTES, BAY_OF_BISCAY, SEA);
    addLink(g, BORDEAUX, BAY_OF_BISCAY, SEA);
    addLink(g, MARSEILLES, MEDITERRANEAN_SEA, SEA );
    addLink(g, GENOA, TYRRHENIAN_SEA, SEA );
    addLink(g, ROME, TYRRHENIAN_SEA, SEA );
    addLink(g, NAPLES, TYRRHENIAN_SEA, SEA);
    addLink(g, SANTANDER, BAY_OF_BISCAY, SEA);
    addLink(g, ALICANTE, MEDITERRANEAN_SEA, SEA);
    addLink(g, LISBON, ATLANTIC_OCEAN, SEA );
    addLink(g, CADIZ, ATLANTIC_OCEAN, SEA );
    addLink(g, BARCELONA, MEDITERRANEAN_SEA, SEA );
    addLink(g, BARI, ADRIATIC_SEA, SEA );
    addLink(g, VENICE, ADRIATIC_SEA, SEA );
    addLink(g, VALONA, IONIAN_SEA, SEA );
    addLink(g, ATHENS, IONIAN_SEA, SEA );
    addLink(g, SALONICA, IONIAN_SEA, SEA );
    addLink(g, VARNA, BLACK_SEA, SEA );
    addLink(g, CONSTANTA, BLACK_SEA, SEA );
    addLink(g, CAGLIARI, MEDITERRANEAN_SEA, SEA );
    addLink(g, CAGLIARI, TYRRHENIAN_SEA, SEA );
    
    //SPANISH SIESTA
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
    addLink(g, SARAGOSSA, BARCELONA, RAIL );
    addLink(g, SARAGOSSA, BARCELONA, LAND );
    addLink(g, SARAGOSSA, ALICANTE, LAND );
    addLink(g, MADRID, SARAGOSSA, LAND );
    addLink(g, MADRID, SARAGOSSA, RAIL );
    addLink(g, SANTANDER, LISBON, LAND );
    addLink(g, SARAGOSSA, BORDEAUX, LAND );
    
    //FRANCY PANTS
    addLink(g, SANTANDER, SARAGOSSA, LAND );
    addLink(g, SARAGOSSA, BORDEAUX, RAIL );
    addLink(g, SARAGOSSA, TOULOUSE, LAND );
    addLink(g, BORDEAUX, TOULOUSE, LAND );
    addLink(g, CLERMONT_FERRAND, TOULOUSE, LAND );
    addLink(g, BORDEAUX, NANTES, LAND );
    addLink(g, NANTES, LE_HAVRE, LAND );
    addLink(g, NANTES, PARIS, LAND );
    addLink(g, PARIS, BORDEAUX, RAIL );
    addLink(g, BORDEAUX, CLERMONT_FERRAND, LAND );
    addLink(g, NANTES, CLERMONT_FERRAND, LAND );
    addLink(g, PARIS, CLERMONT_FERRAND, LAND );
    addLink(g, CLERMONT_FERRAND, MARSEILLES, LAND );
    addLink(g, PARIS, MARSEILLES, RAIL );
    addLink(g, GENEVA, MARSEILLES, LAND );
    addLink(g, GENOA, MARSEILLES, LAND );
    addLink(g, CLERMONT_FERRAND, GENEVA, LAND );
    addLink(g, PARIS, LE_HAVRE, LAND );
    addLink(g, PARIS, LE_HAVRE, RAIL );
    addLink(g, LE_HAVRE, BRUSSELS, LAND );
    addLink(g, PARIS, BRUSSELS, LAND );
    addLink(g, PARIS, BRUSSELS, RAIL );
    addLink(g, TOULOUSE, MARSEILLES, LAND );
    addLink(g, PARIS, GENEVA, LAND );
    
    //VIVE ITALIA!
    addLink(g, MILAN, FLORENCE, RAIL );
    addLink(g, MILAN, GENOA, LAND );
    addLink(g, GENOA, FLORENCE, LAND );
    addLink(g, GENOA, VENICE, LAND );
    addLink(g, GENOA, MILAN, RAIL);
    addLink(g, MILAN, VENICE, LAND );
    addLink(g, FLORENCE, ROME, LAND );
    addLink(g, FLORENCE, ROME, RAIL);
    addLink(g, ROME, BARI, LAND );
    addLink(g, ROME, NAPLES, LAND );
    addLink(g, ROME, NAPLES, RAIL );
    addLink(g, NAPLES, BARI, LAND );
    addLink(g, NAPLES, BARI, RAIL );
    addLink(g, GENEVA, MILAN, RAIL );
    addLink(g, MILAN, ZURICH, LAND );
    addLink(g, MILAN, ZURICH, RAIL );
    addLink(g, MILAN, MARSEILLES, LAND );
    addLink(g, MARSEILLES, ZURICH, LAND );
    addLink(g, GENEVA, ZURICH, LAND );
    addLink(g, VENICE, FLORENCE, LAND );
    
    //YOU ARE MAKING ME HUNGARY
    addLink(g, VIENNA, ZAGREB, LAND );
    addLink(g, VIENNA, BUDAPEST, LAND );
    addLink(g, VIENNA, BUDAPEST, RAIL );
    addLink(g, BUDAPEST, ZAGREB, LAND );
    addLink(g, BUDAPEST, SZEGED, LAND );
    addLink(g, BUDAPEST, SZEGED, RAIL );
    addLink(g, BUDAPEST, KLAUSENBURG, LAND );
    addLink(g, ZAGREB, SZEGED, LAND );
    addLink(g, ZAGREB, ST_JOSEPH_AND_ST_MARYS, LAND );
    addLink(g, SZEGED, ST_JOSEPH_AND_ST_MARYS, LAND );
    addLink(g, SZEGED, KLAUSENBURG, LAND );
    addLink(g, SZEGED, BUCHAREST, RAIL );
    addLink(g, SZEGED, BELGRADE, LAND );
    addLink(g, SZEGED, BELGRADE, RAIL );
    addLink(g, ZAGREB, SARAJEVO, LAND );
    addLink(g, ST_JOSEPH_AND_ST_MARYS, SARAJEVO, LAND );
    addLink(g, ST_JOSEPH_AND_ST_MARYS, BELGRADE, LAND);
    addLink(g, SARAJEVO, BELGRADE, LAND );
    addLink(g, SARAJEVO, VALONA, LAND );
    addLink(g, BELGRADE, KLAUSENBURG, LAND );
    addLink(g, SARAJEVO, SOFIA, LAND );
    addLink(g, BELGRADE, SOFIA, RAIL );
    addLink(g, BELGRADE, BUCHAREST, LAND );
    addLink(g, KLAUSENBURG, CASTLE_DRACULA, LAND );
    addLink(g, KLAUSENBURG, BUCHAREST, LAND );
    addLink(g, KLAUSENBURG, GALATZ, LAND );
    addLink(g, CASTLE_DRACULA, GALATZ, LAND );
    addLink(g, GALATZ, BUCHAREST, LAND );
    addLink(g, GALATZ, BUCHAREST, RAIL );
    addLink(g, GALATZ, CONSTANTA, LAND );
    addLink(g, CONSTANTA, BUCHAREST, LAND );
    addLink(g, CONSTANTA, BUCHAREST, RAIL );
    addLink(g, CONSTANTA, VARNA, LAND );
    addLink(g, BUCHAREST, SOFIA, LAND );
    addLink(g, SOFIA, VARNA, LAND );
    addLink(g, SOFIA, VARNA, RAIL );
    addLink(g, SOFIA, SALONICA, LAND );
    addLink(g, SOFIA, SALONICA, RAIL );
    addLink(g, VALONA, SOFIA, LAND );
    addLink(g, VALONA, SALONICA, LAND);
    addLink(g, VALONA, ATHENS, LAND);
    
    
    //CZECH THIS OUT!
    addLink(g, PRAGUE, VIENNA, RAIL );
    addLink(g, PRAGUE, VIENNA, LAND );
    
}

//Useful for debugging
void showGraph(Graph g) {
    assert(g != NULL);
    printf("V=%d, E=%d + %d\n", g->numVertices, g->numPaths[LAND],g->numPaths[SEA]);
    int i;
    for (i = 0; i < g->numVertices; i++) {
        locList n = g->connections[i];
        while (n != NULL) {
            printf("%d-%d ",i,n->location);
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
    return g->numVertices;
}

int numE(Graph g, Transport type){
    assert(g != NULL);
    assert(type >= 0 && type <= ANY);
    if(type == ANY){
        return g->numPaths[LAND] + g->numPaths[SEA];
    } else {
        return g->numPaths[type];
    }
}

//returns 1 if there is an edge from start to end of the given type
//gives 0 otherwise
int isAdjacent(Graph g,Location start, Location end, Transport type){
    int adjacent = 0;
    locList current = g->connections[start];
    
    while (current != NULL) {
        
        if (current->location == end && current->type == type) {
            adjacent = 1; // true
        } else if (current->location == end && type == ANY) {
            adjacent = 1;
        }
        
        current = current->next;
        
    }
    
    return adjacent;
}


static void doCanReachInN(Graph g, Location start, Transport type, int n, int *locs){
    
    if(n>=0){ //make sure that target is in step radius of start
        
        
        
        if((g->connections[start]->type == type) || (type == ANY)){
            locList current = g->connections[start];
            
            locs[start] = 1;
            
            while(current != NULL){
                doCanReachInN(g, current->location, type, n-1, locs);
                current = current->next;
            }
            
        }else{
            locList current = g->connections[start];
            
            while(current != NULL){
                if(current->type == type){     ///  g->connections[start]->type == type
                    locs[start] = 1;
                    doCanReachInN(g, current->location, type, n-1, locs);
                    
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
void canReachInN(Graph g, Location start, Transport type, int n, int *locs){
    assert(g != NULL);
    
    
    locs[start] = 1;    
   
#ifdef DEBUG_PRINT_LIST 
    printf("n = %d\n", n);
#endif

    doCanReachInN(g, start, type, n, locs);
    
}





void printList(Graph g){
    int listCount = 1;
    
    locList current = g->connections[listCount];
    
    while(listCount < NUM_MAP_LOCATIONS){
        
        current = g->connections[listCount];
        printf("Printing: g->connections[%d]->", listCount);
        
        while(current != NULL){
            printf("[%d][type %d]->", current->location, current->type);
            
            
            current = current->next;
        }
        
        printf("[X]\n");
        listCount++;
    }
}
