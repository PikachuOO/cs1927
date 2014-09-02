#include "game.h"
#include "HunterView.h"
#include "hunter.h"

#include "Graph.h"
#include "Queue.h"
#include "playerData.h"
#include "cities.h"




#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FIRST_ROUND_OFFSET 1
#define MAX_NUM_ROUNDS 366

void decideMove (HunterView gameState) {
   
   //                                               GODAL    SEWAR   HELS    HARK
   int hardCodeMoves[MAX_NUM_ROUNDS][NUM_HUNTERS];

    hardCodeMoves[0][PLAYER_LORD_GODALMING] = GALWAY;
    hardCodeMoves[0][PLAYER_DR_SEWARD] = GALATZ;
    hardCodeMoves[0][PLAYER_VAN_HELSING] = ATHENS;
    hardCodeMoves[0][PLAYER_MINA_HARKER] = MADRID; 
                                                        
   char locStrings[NUM_LOCATIONS][3] = {
     "AL", "AM", "AT", "BA", "BI", "BE", "BR", "BO", "BU",
     "BC", "BD", "CA", "CG", "CD", "CF", "CO", "CN", "DU", "ED",
     "FL", "FR", "GA", "GW", "GE", "GO", "GR", "HA", "JM", "KL",
     "LE",
     "LI", "LS", "LV", "LO", "MA", "MN", "MR", "MI", "MU", "NA",
     "NP", "NU", "PA", "PL", "PR", "RO", "SA", "SN", "SR", "SJ",
     "SO", "ST", "SW", "SZ", "TO", "VA", "VR", "VE", "VI", "ZA",
     "ZU",
     "NS", "EC", "IS", "AO", "BB", "MS", "TS", "IO", "AS", "BS",
     "C?", "S?", "HI", "D1", "D2", "D3", "D4", "D5", "TP"
   };
    
    
   int locCount; 
   
   // LORD_GODALMING turns all set to GALWAY
   for(locCount=0; locCount<MAX_NUM_ROUNDS; locCount++) {
      hardCodeMoves[locCount][PLAYER_LORD_GODALMING] = GALWAY;
   }
   
   // set DR_SEWARD on an alternating path between GALATZ and KLAUSENBURG
   if(getLocation(gameState, gameState->game.whoseTurn) == GALATZ){
      hardCodeMoves[locCount][PLAYER_DR_SEWARD] = KLAUSENBURG;
   }else{
      hardCodeMoves[locCount][PLAYER_DR_SEWARD] = GALATZ;
   }
   
   
   // update VAN_HELSING
   // each turn update the VAN_HELSING hunter to find a random adjacent land city 
   int vanHelsingMove[NUM_LOCATIONS] = {0};

   //city count allows us to keep track of how many available adjacent cities there are to choose from 
   //additionally, it allows us to use locCount as the city number
   int cityCount = 0;
   for(locCount = 0; locCount< NUM_LOCATIONS; locCount++){
      if(isAdjacent(gameState->euroGraph, gameState->hunter[gameState->game.whoseTurn].location, locCount, LAND)){
        vanHelsingMove[cityCount] = locCount; 
        cityCount++;
      }
      locCount++;
   }

   srand(3.1415692);
   int helsRandNum = (rand()) % cityCount;
  
   //use random number and the vanHelsingMove array to populate his move with a random adjacent LAND location 
   hardCodeMoves[locCount][PLAYER_VAN_HELSING] = vanHelsingMove[helsRandNum]; 
   
   // set MINA_HARKER next move
   // harker must move to a random adjacent city by either LAND or SEA   
   int harkerMove[NUM_LOCATIONS] = {0};

   cityCount = 0;
    for(locCount = 0; locCount< NUM_LOCATIONS; locCount++){
       if(isAdjacent(gameState->euroGraph, gameState->hunter[gameState->game.whoseTurn].location, locCount, LAND)){
         harkerMove[cityCount] = locCount; 
         cityCount++;
       }else if(isAdjacent(gameState->euroGraph, gameState->hunter[gameState->game.whoseTurn].location, locCount, SEA)){
         harkerMove[cityCount] = locCount; 
         cityCount++;
       }
       locCount++;
    }

    
    int harkRandNum = (rand()) % cityCount;

    hardCodeMoves[locCount][PLAYER_MINA_HARKER] = harkerMove[harkRandNum]; 

   registerBestPlay(locStrings[hardCodeMoves[gameState->game.roundNumber][gameState->game.whoseTurn]], "Don't cry Callum. - Chris XOXOXO" );
 
}

