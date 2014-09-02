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

#define FIRST_ROUND 0
#define FIRST_ROUND_OFFSET 1
#define MAX_NUM_ROUNDS 366

#define DEBUG

void decideMove (HunterView gameState) {
   
   int bestMove = 0;
   
   //seed random number generator
   srand(3.1415692);
   
   // populate location strings
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
   
   
   // LORD_GODALMING
   // hunter must remain in position at GALWAY.
   if( getCurrentPlayer(gameState) == PLAYER_LORD_GODALMING){
      if(getRound(gameState) == FIRST_ROUND){
         bestMove = GALWAY;
      
      // aknowledged redundancy - using for testing 
      }else{
         bestMove = GALWAY;
      }
      
      
   
   // DR_SEWARD
   // each turn, hunter must alternate between GALATZ and KLAUSENBURG.
   }else if(getCurrentPlayer(gameState) == PLAYER_DR_SEWARD){
      
      if(getRound(gameState) == FIRST_ROUND){
         bestMove = GALATZ;
       
      }else{
         if(getLocation(gameState, PLAYER_DR_SEWARD) == GALATZ){
            bestMove = KLAUSENBURG;
         }else{
            bestMove = GALATZ;
      }

   }
   
   
   // VAN_HELSING
   // each turn, we must update the hunter to find a random adjacent LAND city. 
   }else if(getCurrentPlayer(gameState) == PLAYER_VAN_HELSING){
      
      if(getRound(gameState) == FIRST_ROUND){
         bestMove = ATHENS;
            
      }else{
         int vanHelsingCityCount =0;
         
         LocationID currentLocation;
         currentLocation = getLocation(gameState, PLAYER_VAN_HELSING);
         
         int *vanHelsingMove;
                 
         vanHelsingMove = connectedLocations(gameState, &vanHelsingCityCount, currentLocation, PLAYER_VAN_HELSING, getRound(gameState), 1, 0, 0);

         
         
         #ifdef DEBUG
            printf("currentLocation of VanHels = %d\n", currentLocation);
         #endif
         
         
         int helsRandNum = (rand()) % vanHelsingCityCount; // determine next move for hunter
  
         bestMove = vanHelsingMove[helsRandNum]; 
         
      }
   
   
   // MINA_HARKER
   // each turn, we must update the hunter to find a random adjacent LAND or SEA city. 
   }else if(getCurrentPlayer(gameState) == PLAYER_MINA_HARKER){
      
      if(getRound(gameState) == FIRST_ROUND){
         bestMove = MADRID;
       
      }else{
         int harkerCityCount = 0;
         int *harkerMove;
         LocationID currentLocation = getLocation (gameState, PLAYER_MINA_HARKER);
         
         
         #ifdef DEBUG
            printf("currentLocation of MinHark = %d\n", currentLocation);
         #endif
      
         harkerMove = connectedLocations(gameState, &harkerCityCount, currentLocation, PLAYER_MINA_HARKER, getRound(gameState), 1, 0, 1);

         int harkRandNum = (rand()) % harkerCityCount;

         bestMove = harkerMove[harkRandNum];
      }
   }
   
   registerBestPlay(locStrings[bestMove], "" );
 
}

