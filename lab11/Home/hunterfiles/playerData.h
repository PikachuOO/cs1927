//
//  playerData.h
//  FuryOfDracula
//
//  Created by Callum on 30/09/13.
//  Copyright (c) 2013 Callum. All rights reserved.
//

#ifndef FuryOfDracula_playerData_h
#define FuryOfDracula_playerData_h

#define TRUE 1
#define FALSE 0

#define ENC_TRAP 0
#define ENC_VAMP 1
#define ENC_DRAC 2
#define NUM_ENCS 3

#define ROUNDS_TO_PLACE_V 13
#define ROUNDS_TO_MATURE TRAIL_SIZE
#define UNKNOWN_NUM_ROUNDS -1

#define PLAY_PLAYER         0
#define PLAY_LOC_BEGIN      1
#define PLAY_LOC_END        2
#define H_PLAY_ENC_BEGIN    3
#define H_PLAY_ENC_END      6
#define D_PLAY_ENC_BEGIN    3
#define D_PLAY_ENC_END      4
#define D_PLAY_PLACED_ENC   5
#define PLAY_LENGTH         8

#define NUM_HUNTERS NUM_PLAYERS-1


typedef struct _dracMove {
    int location;
    int roundsSince;
    
} dracMove;


typedef struct _dracStruct {
    int health;
    int surprises[NUM_MAP_LOCATIONS];
    Queue dracLocationQueue;
    
    // extra info for AI
//    dracMove doubleBack;
//    dracMove hidden;
//    dracMove lastKnown;     // last known map location
    int location;
//    int roundsSinceAtSea;
//    int roundsAtSea;
    
    int numMatureVamps;

} dracStruct;


//typedef struct _hunterEncounter {
//    int roundsSince;
//    int encType;
//    //nodePointer next;
//
//} hunterEncounter;


typedef struct _hunterStruct {
    int health;
    int location;
    int encounters[H_PLAY_ENC_END-H_PLAY_ENC_BEGIN];
    //int roundsInHosp;
    //hunterEncounter lastEnc;
    //TODO link previous encounters in the dynamic array
    
} hunterStruct;

#endif
