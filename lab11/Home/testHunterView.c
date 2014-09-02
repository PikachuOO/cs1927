#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cities.h"

#include "Graph.h"

#include "game.h"
#include "HunterView.h"

#define MAX_LOCATION 71


#define ANG_TEST2
#define ANG_TEST3
#define PC_TESTS

//#define DEBUG1
#define LINE "********************************************\n"

void testEmpty(void);
void testNewHunterViewOne(void);
void testNewHunterViewFive(void);
void testNewHunterViewTen(void);
void testNewHunterViewFifteen(void);
void testNewHunterViewFifty(void);
void testGetNoHistory(void);
void testGetShortHistory(void);
void testConnectedLocations(void);
void testGetPLayerTurn(void);
int getTurn (HunterView currentView);


//A sample test program HunterView.h
int main() {
    
#ifdef ANG_TEST2
    int i;
    playerMessage messages[] = {};
	
	
	
    printf("Test basic empty initialisation\n");
    HunterView hv = newHunterView("", messages);
    assert(getCurrentPlayer(hv) == PLAYER_LORD_GODALMING);
    assert(getRound(hv) == 0);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(getScore(hv) == GAME_START_SCORE);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == UNKNOWN_LOCATION);
    
    printf("passed\n");
    disposeHunterView(hv);
	
    playerMessage messages2[] = {"Hello","Rubbish","Stuff","","Mwahahah"};
    printf("Test for Dracula trail and basic functions\n");
    hv = newHunterView("GST.... SAO.... HZU.... MBB.... DC?....", messages2);
    assert(getCurrentPlayer(hv) == PLAYER_LORD_GODALMING);
    assert(getRound(hv) == 1);
    assert(getLocation(hv, PLAYER_LORD_GODALMING) == STRASBOURG);
    assert(getLocation(hv, PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
    assert(getLocation(hv, PLAYER_VAN_HELSING) == ZURICH);
    assert(getLocation(hv, PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
    assert(getLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
    assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    printf("passed\n");
    disposeHunterView(hv);
    
    
    printf("Test for encountering Dracula and hunter history\n");
    playerMessage messages3[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!"};
    hv = newHunterView("GST.... SAO.... HCD.... MAO.... DGE.... GGED...", messages3);
    assert(getLocation(hv,PLAYER_DRACULA) == GENEVA);
    assert(getHealth(hv, PLAYER_LORD_GODALMING) == 5);
    assert(getHealth(hv,PLAYER_DRACULA) == 30);
    assert(getLocation(hv, PLAYER_LORD_GODALMING) == GENEVA);
    LocationID history[TRAIL_SIZE];
    getHistory(hv, PLAYER_DRACULA,history);
    assert(history[0] == GENEVA);
    assert(history[1] == UNKNOWN_LOCATION);
    getHistory(hv, PLAYER_LORD_GODALMING,history);
    assert(history[0] == GENEVA);
    assert(history[1] == STRASBOURG);
    assert(history[2] == UNKNOWN_LOCATION);
    getHistory(hv,PLAYER_DR_SEWARD,history);
    assert(history[0] == ATLANTIC_OCEAN);
    assert(history[1] == UNKNOWN_LOCATION);
    printf("passed\n");
    disposeHunterView(hv);
    
    
    printf("Test for dracula doubling back at sea, and losing blood points\n");
    playerMessage messages4[] = {"Hello","Rubbish","Stuff","","Mwahahah","Aha!","","","","Back I go"};
    hv = newHunterView("GGE.... SGE.... HGE.... MGE.... DS?.... GST.... SST.... HST.... MST.... DD1....", messages4);
    
    assert(getLocation(hv,PLAYER_DRACULA) == DOUBLE_BACK_1);
    getHistory(hv,PLAYER_DRACULA,history);
    assert(history[0] == DOUBLE_BACK_1);
    assert(history[1] == SEA_UNKNOWN);
    assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 4);
    assert(getCurrentPlayer(hv) == 0);
    printf("passed\n");
    disposeHunterView(hv);
    
    
    printf("Test for connections\n");
    int seen[MAX_LOCATION], *edges;
    hv = newHunterView("", messages);
	
    int size;
    edges = connectedLocations(hv,&size, GALATZ,PLAYER_LORD_GODALMING,0,1,0,0);
    memset(seen, 0, MAX_LOCATION*sizeof(int));
    for (i = 0; i< size ; i++) {
        seen[edges[i]] = 1;
    }
    assert(seen[GALATZ]);
    assert(seen[CONSTANTA] && seen[BUCHAREST] && seen[KLAUSENBURG] && seen[CASTLE_DRACULA]);
    assert(size == 5);
    free(edges);
	
    //Checking Ionian seas
    edges = connectedLocations(hv, &size,IONIAN_SEA, PLAYER_LORD_GODALMING, 0 , 0, 0, 1);
    memset(seen, 0, MAX_LOCATION*sizeof(int));
    for (i = 0; i < size; i++) {
        seen[edges[i]] = 1;
    }
    assert(seen[IONIAN_SEA] && seen[BLACK_SEA] && seen[ADRIATIC_SEA] && seen[TYRRHENIAN_SEA]);
    assert(seen[ATHENS] && seen[VALONA] && seen[SALONICA]);
    assert(size == 7);
    free(edges);
    
    edges = connectedLocations(hv, &size,ATHENS,PLAYER_LORD_GODALMING,0,0,1,0);
    assert(size == 1);
    assert(edges[0] == ATHENS);
    free(edges);
    printf("passed\n");
    disposeHunterView(hv);
#endif
    
#ifdef ANG_TEST3
    
    {
    printf("Test 1 Testing just after hunter teleported to hospital...\n");
    playerMessage messages[11] = {"aoeu", "snth", "ABC123", "a", "", "", "a", "b" "c", "d"};
    
    char pastPlays[] = "GMA.... SNP.... HNP.... MNP.... DSR.V.. "
    "GSRVD.. SNP.... HNP.... MNP.... DTOT... "
    "GTOTD..";
    HunterView hv = newHunterView(pastPlays, messages);
    
    
    assert(getHealth(hv,PLAYER_LORD_GODALMING)== GAME_START_HUNTER_LIFE_POINTS);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == ST_JOSEPH_AND_ST_MARYS);
    
    LocationID history[TRAIL_SIZE];
    getHistory(hv,PLAYER_LORD_GODALMING,history);
    assert(history[0] == TOULOUSE);
    assert(history[1] == SARAGOSSA);
    assert(history[2] == MADRID);
    assert(history[3] == UNKNOWN_LOCATION);
    
    assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 2*LIFE_LOSS_HUNTER_ENCOUNTER);
    
    
    disposeHunterView(hv);
    printf("Test 1 passed\n");
    }
    
    {
    printf("Test 2 Testing before next turn for hunter teleported to hospital...\n");
    playerMessage messages[16] = {"aoeu", "snth", "ABC123", "a", "", "", "a", "b" "c", "d"};
    char pastPlays[] =  "GMA.... SNP.... HNP.... MNP.... DSR.V.. "
    "GSRVD.. SNP.... HNP.... MNP.... DTOT... "
    "GTOTD.. SNP.... HNP.... MNP.... DC?T...";
    HunterView hv = newHunterView(pastPlays, messages);
    
    assert(getHealth(hv,PLAYER_LORD_GODALMING)== GAME_START_HUNTER_LIFE_POINTS);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == ST_JOSEPH_AND_ST_MARYS);
    
    LocationID history[TRAIL_SIZE];
    getHistory(hv,PLAYER_LORD_GODALMING,history);
    assert(history[0] == TOULOUSE);
    assert(history[1] == SARAGOSSA);
    assert(history[2] == MADRID);
    assert(history[3] == UNKNOWN_LOCATION);
    
    assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 2*LIFE_LOSS_HUNTER_ENCOUNTER);
    
    disposeHunterView(hv);
    }
    
    {
    printf("Test 3 Testing after next turn for the teleported hunter\n");
    playerMessage messages[17] = {"aoeu", "snth", "ABC123", "a", "", "", "a", "b" "c", "d"};
    
    char pastPlays[] = "GMA.... SNP.... HNP.... MNP.... DSR.V.. "
    "GSRVD.. SNP.... HNP.... MNP.... DTOT... "
    "GTOTD.. SNP.... HNP.... MNP.... DC?T... "
    "GSJ....";
    
    HunterView hv = newHunterView(pastPlays, messages);
    
    assert(getHealth(hv,PLAYER_LORD_GODALMING)== GAME_START_HUNTER_LIFE_POINTS);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == SARAJEVO);
    
    LocationID history[TRAIL_SIZE];
    getHistory(hv,PLAYER_LORD_GODALMING,history);
    assert(history[0] == SARAJEVO);
    assert(history[1] == TOULOUSE);
    assert(history[2] == SARAGOSSA);
    assert(history[3] == MADRID);
    assert(history[4] == UNKNOWN_LOCATION);
    
    assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 2*LIFE_LOSS_HUNTER_ENCOUNTER);
    
    disposeHunterView(hv);
    printf("Test 3 passed\n");
    }
    
    { // modified
        printf("Test 4.5 Testing moving back to place hunter was teleported from\n");
        playerMessage messages[17] = {"aoeu", "snth", "ABC123", "a", "", "", "a", "b" "c", "d"};
        
        char pastPlays[] = "GNP.... SSZ.... HNP.... MNP.... DBE.V.. "
        "GNP.... SBEVD.. HNP.... MNP.... DSJT... "
        "GNP.... SSJTD.. HNP.... MNP.... DSJT... "
        "GNP.... SSJTD..";
        HunterView hv = newHunterView(pastPlays, messages);
        int hunterHealth = GAME_START_HUNTER_LIFE_POINTS -
        LIFE_LOSS_TRAP_ENCOUNTER -
        LIFE_LOSS_DRACULA_ENCOUNTER;
        assert(getHealth(hv,PLAYER_DR_SEWARD) == hunterHealth);
        assert(getLocation(hv,PLAYER_DR_SEWARD) == SARAJEVO);
        
        LocationID history[TRAIL_SIZE];
        getHistory(hv,PLAYER_DR_SEWARD,history);
        assert(history[0] == SARAJEVO);
        assert(history[1] == SARAJEVO);
        assert(history[2] == BELGRADE);
        assert(history[3] == SZEGED);
        assert(history[4] == UNKNOWN_LOCATION);
        
        assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 3*LIFE_LOSS_HUNTER_ENCOUNTER);
        
        disposeHunterView(hv);
        printf("Test 4 passed\n");
    }
    
    {
    printf("Test 4 Testing moving back to place hunter was teleported from\n");
    playerMessage messages[17] = {"aoeu", "snth", "ABC123", "a", "", "", "a", "b" "c", "d"};
    
    char pastPlays[] = "GSZ.... SNP.... HNP.... MNP.... DBE.V.. "
    "GBEVD.. SNP.... HNP.... MNP.... DSJT... "
    "GSJTD.. SNP.... HNP.... MNP.... DSJT... "
    "GSJTD..";
    HunterView hv = newHunterView(pastPlays, messages);
    int hunterHealth = GAME_START_HUNTER_LIFE_POINTS -
    LIFE_LOSS_TRAP_ENCOUNTER -
    LIFE_LOSS_DRACULA_ENCOUNTER;
    assert(getHealth(hv,PLAYER_LORD_GODALMING) == hunterHealth);
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == SARAJEVO);
    
    LocationID history[TRAIL_SIZE];
    getHistory(hv,PLAYER_LORD_GODALMING,history);
    assert(history[0] == SARAJEVO);
    assert(history[1] == SARAJEVO);
    assert(history[2] == BELGRADE);
    assert(history[3] == SZEGED);
    assert(history[4] == UNKNOWN_LOCATION);
    
    assert(getHealth(hv,PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 3*LIFE_LOSS_HUNTER_ENCOUNTER);
    
    disposeHunterView(hv);
    printf("Test 4 passed\n");
    }
    
    
    
    printf("\nAll tests passed\n");
#endif
    
#ifdef PC_TESTS
    printf(LINE);
    printf("Testing hunterView.c... \n");
    
    testEmpty();
    testNewHunterViewOne();
    
    testNewHunterViewFive();
    //testNewHunterViewTen();
    //testNewHunterViewFifteen();
    
    testGetPLayerTurn();
    testGetNoHistory();
    testGetShortHistory();
    testConnectedLocations();
    
    printf("PASSED\n");
    printf(LINE);
#endif
    
    return 0;
}




void testEmpty(void){
    printf("\tTesting empty initialisation...");
    playerMessage messages[] = {};
    HunterView hv = newHunterView("", messages);
    assert(getCurrentPlayer(hv) == PLAYER_LORD_GODALMING);
    assert(getRound(hv) == 0);
    assert(getHealth(hv, PLAYER_DR_SEWARD) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    assert(getScore(hv) == GAME_START_SCORE);
    
    assert(getLocation(hv,PLAYER_LORD_GODALMING) == UNKNOWN_LOCATION);
    assert(getLocation(hv,PLAYER_DR_SEWARD) == UNKNOWN_LOCATION);
    assert(getLocation(hv,PLAYER_VAN_HELSING) == UNKNOWN_LOCATION);
    assert(getLocation(hv,PLAYER_MINA_HARKER) == UNKNOWN_LOCATION);
    assert(getLocation(hv,PLAYER_DRACULA) == UNKNOWN_LOCATION);
    
    disposeHunterView(hv);
    printf("PASSED.\n");
}
void testNewHunterViewOne(void){
    printf("\tTesting newHunterView after 1 round...");
    
    //create game after 1 round, no encounters, everyone at full health
    /*ROUNDS COMPLETE: 1
     * NO ENCOUNTERS
     * HUNTERS FULL HEALTH
     * DRACULA FULL HEALTH
     * DRACULA PLACES TRAP
     *
     * FINAL LOCATIONS:
     * PLAYER_LORD_GODALMING  at LONDON
     * PLAYER_DR_SEWARD       at CAGLIARI
     * PLAYER_VAN_HELSING     at ClERMONT_FERRAND
     * PLAYER_MINA_HARKER     at BERLIN
     * PLAYER_DRACULA         at UNKNOWN_LOCATION (LE_HAVRE)
     *
     */
    
    
    playerMessage messages[] = {};
    char pastPlays[] = {"GLO.... SCG.... HCF.... MBR.... DC?T... "}; //D->LE_HAVRE
    HunterView hunterViewOne = newHunterView(pastPlays, messages);
    
#ifdef DEBUG1
    printf("\npastPlays is: \n");
    printf("*** %s ***\n", pastPlays);
#endif
    
    //check turn numbers
    assert(getTurn(hunterViewOne) == 5);
    
    //check roundCount !!is this right?
    assert(getRound(hunterViewOne) == 1);
    
    //check current player
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_LORD_GODALMING);
    
    //check hunter health
    assert(getHealth(hunterViewOne, PLAYER_LORD_GODALMING ) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hunterViewOne, PLAYER_DR_SEWARD ) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hunterViewOne, PLAYER_VAN_HELSING ) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hunterViewOne, PLAYER_MINA_HARKER ) == GAME_START_HUNTER_LIFE_POINTS);
    
    //check Dracula health
    assert(getHealth(hunterViewOne, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
    
    //check game score (remember to check if there have been encounters/life loss etc)
    assert(getScore(hunterViewOne) == GAME_START_SCORE-1);
    
    
    assert(getLocation(hunterViewOne,PLAYER_LORD_GODALMING ) == LONDON);
    assert(getLocation(hunterViewOne,PLAYER_DR_SEWARD ) == CAGLIARI);
    assert(getLocation(hunterViewOne,PLAYER_VAN_HELSING ) == CLERMONT_FERRAND);
    assert(getLocation(hunterViewOne,PLAYER_MINA_HARKER ) == BERLIN);
    assert(getLocation(hunterViewOne,PLAYER_DRACULA ) == CITY_UNKNOWN);
    
    printf("PASSED.\n");
}
void testNewHunterViewFive(void){
    printf("\tTesting newHunterView after 5 rounds...");
    
    //create game after 1 round, no encounters, everyone at full health
    /*ROUNDS COMPLETE: 5
     * 3 ENCOUNTERS
     * 2 HUNTERS FULL HEALTH
     *
     * DRACULA HALF HEALTH
     *
     * FINAL LOCATIONS:
     * PLAYER_LORD_GODALMING  at LONDON
     * PLAYER_DR_SEWARD       at VENICE
     * PLAYER_VAN_HELSING     at MILAN
     * PLAYER_MINA_HARKER     at ZURICH
     * PLAYER_DRACULA         at UNKNOWN_LOCATION (MUNICH)
     *
     * PAST PLAYS CODA:
     * '->'  == goes to, or moves to
     * '*'   == some form of encounter, trap or otherwise
     */
    
    //! this string is incorrect, drac location hasn't been updated
    playerMessage messages[] = {};
    char pastPlays[] =
    {"GLO.... SCG.... HCF.... MBR.... DC?T... "   //D-> LE_HAVRE,
        "GSW.... SMS.... HPAD... MLI.... DPAT... "   //D-> PARIS,      HELSING * DRAC
        "GLV.... SMR.... HGE.... MNU.... DC?T... "   //D-> STRASBOURG,
        "GMN.... SMI.... HZUD... MSTT... DZUT... "   //D-> ZURICH,     HELSING * DRAC, HARKER * TRAP
        "GLO.... SVE.... HMI.... MZU.... DC?T... "}; //D-> MUNICH,
    
#ifdef DEBUG1
    printf("\npastPlays is: \n");
    printf("*** %s ***\n", pastPlays);
#endif
    
    HunterView hunterViewOne = newHunterView(pastPlays, messages);
    
    //check turn numbers
    assert(getTurn(hunterViewOne) == 25);
    
    //check roundCount
    assert(getRound(hunterViewOne) == 5);  // end of round 4
    
    
    //check game score
    int numDracTurns = (int)(getTurn(hunterViewOne)/NUM_PLAYERS);
    int currentScore = GAME_START_SCORE-numDracTurns*SCORE_LOSS_DRACULA_TURN;
    assert(getScore(hunterViewOne) == currentScore);
    
    //check current player
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_LORD_GODALMING);
    
    //check hunter health
    assert(getHealth(hunterViewOne, PLAYER_LORD_GODALMING ) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hunterViewOne, PLAYER_DR_SEWARD ) == GAME_START_HUNTER_LIFE_POINTS);
    assert(getHealth(hunterViewOne, PLAYER_VAN_HELSING ) == GAME_START_HUNTER_LIFE_POINTS - 2*LIFE_LOSS_DRACULA_ENCOUNTER);
    assert(getHealth(hunterViewOne, PLAYER_MINA_HARKER ) == GAME_START_HUNTER_LIFE_POINTS - LIFE_LOSS_TRAP_ENCOUNTER);
    
    //check Dracula health
    assert(getHealth(hunterViewOne, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS - 2* LIFE_LOSS_HUNTER_ENCOUNTER);
    
    
    assert(getLocation(hunterViewOne,PLAYER_LORD_GODALMING ) == LONDON);
    assert(getLocation(hunterViewOne,PLAYER_DR_SEWARD ) == VENICE);
    assert(getLocation(hunterViewOne,PLAYER_VAN_HELSING ) == MILAN);
    assert(getLocation(hunterViewOne,PLAYER_MINA_HARKER ) == ZURICH);
    assert(getLocation(hunterViewOne,PLAYER_DRACULA ) == CITY_UNKNOWN);
    
    printf("PASSED.\n");
}

void testNewHunterViewTen(void){
    printf("\tTesting newHunterView after 10 rounds...");
    
    //create game after 1 round, no encounters, everyone at full health
    /*ROUNDS COMPLETE: 5
     * 3 ENCOUNTERS
     * 2 HUNTERS FULL HEALTH
     *
     * DRACULA HALF HEALTH
     *
     * FINAL LOCATIONS:
     * PLAYER_LORD_GODALMING  at MADRID
     * PLAYER_DR_SEWARD       at BUCHAREST
     * PLAYER_VAN_HELSING     at ST_JOSEPH_AND_ST_MARYS (CASUALTY)
     * PLAYER_MINA_HARKER     at KLAUSENBURG
     * PLAYER_DRACULA         at UNKNOWN_LOCATION (GALLATZ)
     *
     * PAST PLAYS CODA:
     * '->'  == goes to, or moves to
     * '*'   == some form of encounter, trap or otherwise
     */
    
    
    playerMessage messages[] = {};
    char pastPlays[] =
    {"GLO.... SCG.... HCF.... MBR.... DC?T... "   //D-> LE_HAVRE,
        "GSW.... SMS.... HPAD... MLI.... DPAT... "   //D-> PARIS,        HELS * DRAC
        "GLV.... SMR.... HGE.... MNU.... DC?T... "   //D-> STRASBOURG,
        "GMN.... SMI.... HZUD... MSTT... DZUT... "   //D-> ZURICH,       HELS * DRAC, HARK * TRAP
        "GLO.... SVE.... HMI.... MZU.... DC?T... "   //D-> MUNICH,
        
        "GEC.... SVID... HMUT... MMI.... DVIT... "   //D-> VIENNA,       SEWA * DRAC, HELS * TRAP
        "GLET... SZA.... HPAD... MVE.... DBDT... "   //D-> BUDAPEST
        "GNA.... SSZ.... HGE.... MVIT... DD3T... "   //D-> (DB3) MUNICH, MUNICH = 2 * TRAP, HARK * TRAP
        "GBB.... SBE.... HZUD... MBDT... DTP.... "   //D-> TELEPORT,     HARK * TRAP
        "GMA.... SBC.... HJM.... MKL.... DC?T... "}; //D-> GALLATZ
    
    HunterView hunterViewOne = newHunterView(pastPlays, messages);
    
#ifdef DEBUG1
    printf("\npastPlays is: \n");
    printf("*** %s ***\n", pastPlays);
#endif
    
    //check turn numbers
    assert(getTurn(hunterViewOne) == 50);
    
    //check roundCount
    assert(getRound(hunterViewOne) == 10);
    
    
    //check game score
    int numDracTurns = (int)(getTurn(hunterViewOne)/NUM_PLAYERS);
    int currentScore = GAME_START_SCORE-(numDracTurns*SCORE_LOSS_DRACULA_TURN);
    assert(getScore(hunterViewOne) == currentScore);
    
    //check current player
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_LORD_GODALMING);
    
    //check hunter health
    assert(getHealth(hunterViewOne, PLAYER_LORD_GODALMING ) == (GAME_START_HUNTER_LIFE_POINTS) - (LIFE_LOSS_TRAP_ENCOUNTER));
    assert(getHealth(hunterViewOne, PLAYER_DR_SEWARD ) == (GAME_START_HUNTER_LIFE_POINTS - (LIFE_LOSS_DRACULA_ENCOUNTER)));
    assert(getHealth(hunterViewOne, PLAYER_VAN_HELSING ) == (GAME_START_HUNTER_LIFE_POINTS - (2*LIFE_LOSS_DRACULA_ENCOUNTER) - (LIFE_LOSS_TRAP_ENCOUNTER))); //TODO !!this test might be wrong. Depends on timing of health restoration
    assert(getHealth(hunterViewOne, PLAYER_MINA_HARKER ) == (GAME_START_HUNTER_LIFE_POINTS - (3*LIFE_LOSS_TRAP_ENCOUNTER)));
    
    //check Dracula health
    assert(getHealth(hunterViewOne, PLAYER_DRACULA) == (GAME_START_BLOOD_POINTS - (3* LIFE_LOSS_HUNTER_ENCOUNTER)));
    
    
    assert(getLocation(hunterViewOne,PLAYER_LORD_GODALMING ) == MADRID);
    assert(getLocation(hunterViewOne,PLAYER_DR_SEWARD ) == BUCHAREST);
    assert(getLocation(hunterViewOne,PLAYER_VAN_HELSING ) == ST_JOSEPH_AND_ST_MARYS);
    assert(getLocation(hunterViewOne,PLAYER_MINA_HARKER ) == KLAUSENBURG);
    assert(getLocation(hunterViewOne,PLAYER_DRACULA ) == CITY_UNKNOWN);
    
    printf("PASSED.\n");
}




void testNewHunterViewFifteen(void){
    printf("\tTesting newHunterView after 15 rounds...");
    
    //create game after 1 round, no encounters, everyone at full health
    /*ROUNDS COMPLETE: 15
     *
     *
     *
     *
     *
     * FINAL LOCATIONS:
     * PLAYER_LORD_GODALMING  at ZURICH
     * PLAYER_DR_SEWARD       at MUNICH
     * PLAYER_VAN_HELSING     at VARNA
     * PLAYER_MINA_HARKER     at SALONICA
     * PLAYER_DRACULA         at UNKNOWN_LOCATION (VALONA)
     *
     * PAST PLAYS CODA:
     * '->'  == goes to, or moves to
     * '*'   == some form of encounter, trap or otherwise
     */
    
    
    playerMessage messages[] = {};
    char pastPlays[] =
    {"GLO.... SCG.... HCF.... MBR.... DC?T... "   //D-> LE_HAVRE,
        "GSW.... SMS.... HPAD... MLI.... DPAT... "   //D-> PARIS,        HELS * DRAC
        "GLV.... SMR.... HGE.... MNU.... DC?T... "   //D-> STRASBOURG,
        "GMN.... SMI.... HZUD... MSTT... DZUT... "   //D-> ZURICH,       HELS * DRAC, HARK * TRAP
        "GLO.... SVE.... HMI.... MZUT... DC?T... "   //D-> MUNICH,
        
        "GEC.... SVID... HMUT... MMI.... DVIT... "   //D-> VIENNA,       SEWA * DRAC, HELS * TRAP
        "GLET... SZA.... HPAD... MVE.... DC?T... "   //D-> BUDAPEST
        "GNA.... SSZ.... HGE.... MVIT... DD3T... "   //D-> (DB3) MUNICH, MUNICH = 2 * TRAP, HARK * TRAP
        "GBB.... SBE.... HZUD... MBDT... DTPT... "   //D-> TELEPORT,     HARK * TRAP
        "GMA.... SBC.... HJM.... MKL.... DC?T... "   //D-> GALLATZ
        
        "GSR.... SKL.... HBE.... MGAT... DC?T... "   //D-> CONSTANTA, HARK * TRAP
        "GTO.... SBD.... HSO.... MJM.... DC?T... "   //D-> BLACK_SEA - LOSEHEALTH, HARK * STJM
        "GCF.... SZA.... HSA.... MSJ.... DC?V... "   //D-> VARNA, DRAC * BABY_VAMP,
        "GGE.... SVIT... HBS.... MSO.... DC?T... "   //D-> (DB6) MUNICH, MUNICH = 3 * TRAP,
        "GZU.... SMUTTT. HVRV... MSA.... DC?T... "}; //D-> VALONA, HELS * BABY VAMP, SEWA * 3* TRAP
    
    HunterView hunterViewOne = newHunterView(pastPlays, messages);
    
#ifdef DEBUG1
    printf("\npastPlays is: \n");
    printf("*** %s ***\n", pastPlays);
#endif
    
    //check turn numbers
    assert(getTurn(hunterViewOne) == 75);
    
    //check roundCount
    assert(getRound(hunterViewOne) == 15);
    
    
    //check game score
    int currentScore = GAME_START_SCORE-(getRound(hunterViewOne)*SCORE_LOSS_DRACULA_TURN);
    assert(getScore(hunterViewOne) == currentScore);
    
    //check current player
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_LORD_GODALMING);
    
    //check hunter health
    assert(getHealth(hunterViewOne, PLAYER_LORD_GODALMING ) == (GAME_START_HUNTER_LIFE_POINTS) - (LIFE_LOSS_TRAP_ENCOUNTER));
    assert(getHealth(hunterViewOne, PLAYER_DR_SEWARD ) == (GAME_START_HUNTER_LIFE_POINTS - (LIFE_LOSS_DRACULA_ENCOUNTER) - 4*LIFE_LOSS_TRAP_ENCOUNTER));
    assert(getHealth(hunterViewOne, PLAYER_VAN_HELSING ) == (GAME_START_HUNTER_LIFE_POINTS - (2*LIFE_LOSS_DRACULA_ENCOUNTER) - (LIFE_LOSS_TRAP_ENCOUNTER)));
    assert(getHealth(hunterViewOne, PLAYER_MINA_HARKER ) == (GAME_START_HUNTER_LIFE_POINTS));
    //HARKER should be back to full health after stay in JM.
    
    
    //check Dracula health
    assert(getHealth(hunterViewOne, PLAYER_DRACULA) == (GAME_START_BLOOD_POINTS - (2* LIFE_LOSS_HUNTER_ENCOUNTER) + LIFE_GAIN_CASTLE_DRACULA - LIFE_LOSS_SEA));
    
    
    assert(getLocation(hunterViewOne,PLAYER_LORD_GODALMING ) == ZURICH);
    assert(getLocation(hunterViewOne,PLAYER_DR_SEWARD ) == MUNICH);
    assert(getLocation(hunterViewOne,PLAYER_VAN_HELSING ) == VARNA);
    assert(getLocation(hunterViewOne,PLAYER_MINA_HARKER ) == SALONICA);
    assert(getLocation(hunterViewOne,PLAYER_DRACULA ) == CITY_UNKNOWN);
    
    printf("PASSED.\n");
}

void testGetPLayerTurn(void){
    printf("\t Testing getTurn...");
    
    playerMessage messages[] = {};
    char pastPlays0[] = {"GLO.... SCG.... HCF.... MBR.... DC?.... "};
    
#ifdef DEBUG
    printf("\npast plays is:\n%s\n", pastPlays0);
#endif
    
    HunterView hunterViewOne = newHunterView(pastPlays0, messages);
    
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_LORD_GODALMING);
    
    char pastPlays1[] = {"GLO.... SCG.... HCF.... MBR.... "};
    hunterViewOne = newHunterView(pastPlays1, messages);
    
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_DRACULA);
    
    char pastPlays2[] = {"GLO.... SCG.... HCF.... "};
    hunterViewOne = newHunterView(pastPlays2, messages);
    
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_MINA_HARKER);
    
    char pastPlays3[] = {"GLO.... SCG.... "};
    hunterViewOne = newHunterView(pastPlays3, messages);
    
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_VAN_HELSING);
    
    char pastPlays4[] = {"GLO.... "};
    hunterViewOne = newHunterView(pastPlays4, messages);
    
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_DR_SEWARD);
    
    char pastPlays5[] = {""};
    hunterViewOne = newHunterView(pastPlays5, messages);
    
    assert(getCurrentPlayer(hunterViewOne) == PLAYER_LORD_GODALMING);
    
    printf("PASSED.\n");
}

void testGetNoHistory(void){
    printf("\tTesting getHistory on an empty game...");
    
    char pastPlays[] = {""}; //empty past plays -> start of game
    playerMessage messages[] = {};
    
    HunterView hunterViewOne = newHunterView(pastPlays, messages);
    
    int trailGODA[TRAIL_SIZE] = {0};
    int trailSEWA[TRAIL_SIZE] = {0};
    int trailHELS[TRAIL_SIZE] = {0};
    int trailHARK[TRAIL_SIZE] = {0};
    int trailDRAC[TRAIL_SIZE] = {0};
    
    //PLAYER_LORD_GODALMING HISTORY
    getHistory (hunterViewOne, PLAYER_LORD_GODALMING, trailGODA);
    assert(trailGODA[0] == UNKNOWN_LOCATION);
    assert(trailGODA[1] == UNKNOWN_LOCATION);
    assert(trailGODA[2] == UNKNOWN_LOCATION);
    assert(trailGODA[3] == UNKNOWN_LOCATION);
    assert(trailGODA[4] == UNKNOWN_LOCATION);
    assert(trailGODA[5] == UNKNOWN_LOCATION);
    
    //PLAYER_DR_SEWARD HISTORY
    getHistory (hunterViewOne, PLAYER_DR_SEWARD,  trailSEWA);
    assert(trailSEWA[0] == UNKNOWN_LOCATION);
    assert(trailSEWA[1] == UNKNOWN_LOCATION);
    assert(trailSEWA[2] == UNKNOWN_LOCATION);
    assert(trailSEWA[3] == UNKNOWN_LOCATION);
    assert(trailSEWA[4] == UNKNOWN_LOCATION);
    assert(trailSEWA[5] == UNKNOWN_LOCATION);
    
    //PLAYER_VAN_HELSING HISTORY
    getHistory (hunterViewOne, PLAYER_VAN_HELSING,  trailHELS);
    assert(trailHELS[0] == UNKNOWN_LOCATION);
    assert(trailHELS[1] == UNKNOWN_LOCATION);
    assert(trailHELS[2] == UNKNOWN_LOCATION);
    assert(trailHELS[3] == UNKNOWN_LOCATION);
    assert(trailHELS[4] == UNKNOWN_LOCATION);
    assert(trailHELS[5] == UNKNOWN_LOCATION);
    
    //PLAYER_MINA_HARKER HISTORY
    getHistory (hunterViewOne, PLAYER_MINA_HARKER,  trailHARK);
    assert(trailHARK[0] == UNKNOWN_LOCATION);
    assert(trailHARK[1] == UNKNOWN_LOCATION);
    assert(trailHARK[2] == UNKNOWN_LOCATION);
    assert(trailHARK[3] == UNKNOWN_LOCATION);
    assert(trailHARK[4] == UNKNOWN_LOCATION);
    assert(trailHARK[5] == UNKNOWN_LOCATION);
    
    //PLAYER_DRACULA HISTORY
    getHistory (hunterViewOne, PLAYER_DRACULA,  trailDRAC);
    assert(trailDRAC[0] == UNKNOWN_LOCATION);
    assert(trailDRAC[1] == UNKNOWN_LOCATION);
    assert(trailDRAC[2] == UNKNOWN_LOCATION);  //DOUBLE BACK 3 SPACES
    assert(trailDRAC[3] == UNKNOWN_LOCATION);
    assert(trailDRAC[4] == UNKNOWN_LOCATION);
    assert(trailDRAC[5] == UNKNOWN_LOCATION);
    
    printf("PASSED.\n");
}


void testGetShortHistory(void){
    printf("\tTesting getHistory on a game with 6+ turns ...");
    
    char pastPlays[] =
    {"GLO.... SCG.... HCF.... MBR.... DC?T... "   //D-> LE_HAVRE,
        "GSW.... SMS.... HPA...D MLI.... DPAT... "   //D-> PARIS,        HELS * DRAC
        "GLV.... SMR.... HGE.... MNU.... DC?T... "   //D-> STRASBOURG,
        "GMN.... SMI.... HZU...D MSTT... DZUT... "   //D-> ZURICH,       HELS * DRAC, HARK * TRAP
        "GLO.... SVE.... HMI.... MZU.... DC?T... "   //D-> MUNICH,
        
        "GEC.... SVI...D HMUT... MMI.... DVIT... "
        "GLET... SZA.... HZU...D MVE.... DBDT... "   //D-> BUDAPEST
        "GNA.... SSZ.... HGE.... MVIT... DD3T... "   //D-> (DB3) MUNICH, MUNICH = 2 * TRAP, HARK * TRAP
        "GBB.... SBE.... HZU...D MBDT... DTP.... "   //D-> TELEPORT,     HARK * TRAP
        "GMA.... SBC.... HJM.... MKL.... DC?T... "}; //D-> GALLATZ
    
    playerMessage messages[] = {};
    
    HunterView hunterViewOne = newHunterView(pastPlays, messages);
    
    int trailGODA[TRAIL_SIZE] = {0};
    int trailSEWA[TRAIL_SIZE] = {0};
    int trailHELS[TRAIL_SIZE] = {0};
    int trailHARK[TRAIL_SIZE] = {0};
    int trailDRAC[TRAIL_SIZE] = {0};
    
    //PLAYER_LORD_GODALMING HISTORY
    getHistory (hunterViewOne, PLAYER_LORD_GODALMING,  trailGODA);
    
    
#ifdef DEBUG1
    printf("\n");
    printf("trailGODA[0] = %d\n", trailGODA[0]);
    printf("trailGODA[1] = %d\n", trailGODA[1]);
    printf("trailGODA[2] = %d\n", trailGODA[2]);
    printf("trailGODA[3] = %d\n", trailGODA[3]);
    printf("trailGODA[4] = %d\n", trailGODA[4]);
    printf("trailGODA[5] = %d\n", trailGODA[5]);
#endif
    
    
    assert(trailGODA[0] == MADRID);
    assert(trailGODA[1] == BAY_OF_BISCAY);
    assert(trailGODA[2] == NANTES);
    assert(trailGODA[3] == LE_HAVRE);
    assert(trailGODA[4] == ENGLISH_CHANNEL);
    assert(trailGODA[5] == LONDON);
    
    //PLAYER_DR_SEWARD HISTORY
    getHistory (hunterViewOne, PLAYER_DR_SEWARD,  trailSEWA);
    
#ifdef DEBUG1
    printf("\n");
    printf("trailSEWA[0] = %d\n", trailSEWA[0]);
    printf("trailSEWA[1] = %d\n", trailSEWA[1]);
    printf("trailSEWA[2] = %d\n", trailSEWA[2]);
    printf("trailSEWA[3] = %d\n", trailSEWA[3]);
    printf("trailSEWA[4] = %d\n", trailSEWA[4]);
    printf("trailSEWA[5] = %d\n", trailSEWA[5]);
#endif
    
    assert(trailSEWA[0] == BUCHAREST);
    assert(trailSEWA[1] == BELGRADE);
    assert(trailSEWA[2] == SZEGED);
    assert(trailSEWA[3] == ZAGREB);
    assert(trailSEWA[4] == VIENNA);
    assert(trailSEWA[5] == VENICE);
    
    //PLAYER_VAN_HELSING HISTORY
    getHistory (hunterViewOne, PLAYER_VAN_HELSING,  trailHELS);
    
#ifdef DEBUG1
    printf("\n");
    printf("trailHELS[0] = %d\n", trailHELS[0]);
    printf("trailHELS[1] = %d\n", trailHELS[1]);
    printf("trailHELS[2] = %d\n", trailHELS[2]);
    printf("trailHELS[3] = %d\n", trailHELS[3]);
    printf("trailHELS[4] = %d\n", trailHELS[4]);
    printf("trailHELS[5] = %d\n", trailHELS[5]);
#endif
    
    assert(trailHELS[0] == ST_JOSEPH_AND_ST_MARYS);
    assert(trailHELS[1] == ZURICH);
    assert(trailHELS[2] == GENEVA);
    assert(trailHELS[3] == ZURICH);
    assert(trailHELS[4] == MUNICH);
    assert(trailHELS[5] == MILAN);
    
    //PLAYER_MINA_HARKER HISTORY
    getHistory (hunterViewOne, PLAYER_MINA_HARKER,  trailHARK);
    
#ifdef DEBUG1
    printf("\n");
    printf("trailHARK[0] = %d\n", trailHARK[0]);
    printf("trailHARK[1] = %d\n", trailHARK[1]);
    printf("trailHARK[2] = %d\n", trailHARK[2]);
    printf("trailHARK[3] = %d\n", trailHARK[3]);
    printf("trailHARK[4] = %d\n", trailHARK[4]);
    printf("trailHARK[5] = %d\n", trailHARK[5]);
#endif
    
    assert(trailHARK[0] == KLAUSENBURG);
    assert(trailHARK[1] == BUDAPEST);
    assert(trailHARK[2] == VIENNA);
    assert(trailHARK[3] == VENICE);
    assert(trailHARK[4] == MILAN);
    assert(trailHARK[5] == ZURICH);
    
    //PLAYER_DRACULA HISTORY
    getHistory (hunterViewOne, PLAYER_DRACULA,  trailDRAC);
    
#ifdef DEBUG1
    printf("\n");
    printf("trailDRAC[0] = %d\n", trailDRAC[0] );
    printf("trailDRAC[1] = %d\n", trailDRAC[1] );
    printf("trailDRAC[2] = %d\n", trailDRAC[2] );
    printf("trailDRAC[3] = %d\n", trailDRAC[3] );
    printf("trailDRAC[4] = %d\n", trailDRAC[4] );
    printf("trailDRAC[5] = %d\n", trailDRAC[5] );
#endif
    
    assert(trailDRAC[0] == CITY_UNKNOWN);
    assert(trailDRAC[1] == TELEPORT); //when teleport, LOCATION is CASTLE DRAC
    assert(trailDRAC[2] == DOUBLE_BACK_3);  //DOUBLE BACK 3 SPACES
    assert(trailDRAC[3] == BUDAPEST);
    assert(trailDRAC[4] == VIENNA);
    assert(trailDRAC[5] == CITY_UNKNOWN);
    
    char pastPlaysDracSpecial[] =
    {"GLO.... SCG.... HCF.... MBR.... DC?T... GSW...."};
    
    hunterViewOne = newHunterView(pastPlaysDracSpecial, messages);
    
    getHistory (hunterViewOne, PLAYER_DRACULA,  trailDRAC);
    
    
    printf("PASSED.\n");
}
void testConnectedLocations(void){
    printf("\tTesting connectedLocations...");
    
    playerMessage messages[100] = {};
    
    int seen[MAX_LOCATION], *edges;
    HunterView hv = newHunterView("", messages);
    int i = 0;
    int size;
    
    /*
    * START AT PARIS
    * Bordeaux 7
    * Brussels 8
    * Clermont Ferrand 14
    * Geneva 23
    * Le Havre 29 
    * Marseilles 36
    * Nantes 39
    * Strasbourg 51 !!!!!!!!!!!!!!!!!
    *
    */

    edges = connectedLocations(hv,&size, PARIS ,PLAYER_LORD_GODALMING,1,1,1,0);
    memset(seen, 0, MAX_LOCATION*sizeof(int));
    for (i = 0; i< size ; i++) {
        seen[edges[i]] = 1;
    }


    
    printf("TESTING PARIS,\n--1 STEP\nSize = %d\n", size);    
    int printCount = 0;    
    while(printCount < MAX_LOCATION){
        if(seen[printCount] != 0){
            printf("seen[%d] = %d\n",printCount, seen[printCount]);
            
        }
        printCount++;

    }

    free(edges);
    

   
    edges = connectedLocations(hv, &size,FRANKFURT, PLAYER_LORD_GODALMING, 0 , 1, 1, 1);
    memset(seen, 0, MAX_LOCATION*sizeof(int));
    for (i = 0; i < size; i++) {
        seen[edges[i]] = 1;
    }

    printf("TESTING FRANKFURT,\n--1 STEP\nSize = %d\n", size);
    printCount = 0;
    while(printCount < MAX_LOCATION){
        if(seen[printCount] != 0){
            printf("seen[%d] = %d\n",printCount, seen[printCount]);
            
        }
        printCount++;

    }



    free(edges);
    
    edges = connectedLocations(hv, &size,SZEGED, PLAYER_LORD_GODALMING, 0 , 1, 1, 1);
    memset(seen, 0, MAX_LOCATION*sizeof(int));
    for (i = 0; i < size; i++) {
        seen[edges[i]] = 1;
    }

    printf("TESTING SZEGED,\n--1 STEP\nSize = %d\n",size );
    printCount = 0;
    while(printCount < MAX_LOCATION){
        
        if(seen[printCount] != 0){
            printf("seen[%d] = %d\n",printCount, seen[printCount]);
            
        }
        printCount++;
    }


    free(edges);

    edges = connectedLocations(hv, &size,MADRID, PLAYER_LORD_GODALMING, 0 , 1, 1, 1);
    memset(seen, 0, MAX_LOCATION*sizeof(int));
    for (i = 0; i < size; i++) {
        seen[edges[i]] = 1;
    }

    printf("TESTING MADRID,\n--1 STEP\nSize = %d\n", size);
    printCount = 0;
    while(printCount < MAX_LOCATION){
        if(seen[printCount] != 0){
            printf("seen[%d] = %d\n",printCount, seen[printCount]);
            
        }
        printCount++;
    }


    free(edges);


    edges = connectedLocations(hv, &size,MARSEILLES,PLAYER_LORD_GODALMING,0,1,1,1);
   
    printf("TESTING MARSEILLES,\n--1 STEP\nSize = %d\n", size);
    printCount = 0;
    while(printCount < MAX_LOCATION){
        if(seen[printCount] != 0){
            printf("seen[%d] = %d\n",printCount, seen[printCount]);
            
        }
        printCount++;
    }




    free(edges);
    printf("passed\n");
    disposeHunterView(hv);

    printf("PASSED.\n");
}
