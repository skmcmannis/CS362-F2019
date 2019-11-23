//Unit Test 1 - Baron
//Author: Shawn McMannis
//CS 362 Software Engineering II
//Last Mod Date: 11/8/2019

#include "dominion.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Declare game states
	struct gameState G;
	struct gameState O;

	//Delcare arrays
	int estates[MAX_HAND];
	for(int i = 0; i < MAX_HAND; i++){
		estates[i] = estate;
	}
	int duchys[MAX_HAND];
	for(int j = 0; j < MAX_HAND; j++){
		duchys[j] = duchy;
	}

	//Delcare random seed
	int seed = time(NULL);

	//Declare maximum hand size
	int handCount = 1;

	printf("Begin Testing Baron:\n");

	//TEST 1: Discard estate with estate in hand
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	int r = initializeGame(2, k, seed, &G);

	//Set hand to all estates
	G.handCount[1] = handCount;
	memcpy(G.hand[1], estates, sizeof(int) * handCount);

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	baronEffect(1, 1, &G);

	COMPARE(G.coins == O.coins + 4); //Verify coins added
	COMPARE(G.discard[1][0] == estate); //Verify estate in discard pile
	COMPARE(G.discardCount[1] == 1); //Verify one card in discard pile
	COMPARE(G.handCount[1] == handCount - 1); //Verify handCount reduced by one


	//TEST 2: Discard estate with no estate in hand and estate supply > 0
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand count and composition
	G.handCount[1] = handCount;
	memcpy(G.hand[1], duchys, sizeof(int) * MAX_HAND);
	
	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	baronEffect(1, 1, &G);

	COMPARE(supplyCount(estate, &G) == supplyCount(estate, &O) - 1); //Verify estate supplyCount reduced by one
	COMPARE(G.discardCount[1] == O.discardCount[1] + 1); //Verify discard count increased by one
	COMPARE(G.discard[1][0] == estate); //Verify estate placed in discard


	//TEST 3: Discard estate with no estate in hand and estate supply == 0
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand count and composition
	G.handCount[1] = handCount;
	memcpy(G.hand[1], duchys, sizeof(int) * MAX_HAND);
	
	//Set estate supply to 0
	G.supplyCount[estate] = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	baronEffect(1, 1, &G);

	//Verify no relevant changes to game state
	COMPARE(supplyCount(estate, &G) == supplyCount(estate, &O));
	COMPARE(G.discardCount[1] == O.discardCount[1]);
	COMPARE(G.discard[1][0] != estate);


	//TEST 4: Discard estate with no estate in hand and estate supply == 2
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand count and composition
	G.handCount[1] = handCount;
	memcpy(G.hand[1], duchys, sizeof(int) * MAX_HAND);
	
	//Set estate supply to 2
	G.supplyCount[estate] = 2;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	baronEffect(1, 1, &G);

	COMPARE(supplyCount(estate, &G) == 0); //Verify supplyCount of estate is 0
	COMPARE(isGameOver(&G) == 0); //Verify game is not over
	COMPARE(G.discardCount[1] == O.discardCount[1] + 1); //Verify discard count increased by one
	COMPARE(G.discard[1][0] == estate); //Verify estate placed in discard
	
	
	//TEST 5: Do not discard estate with estate supply > 0
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand count and composition
	G.handCount[1] = handCount;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	baronEffect(0, 1, &G);

	//Verify no relevant changes to game state
	COMPARE(supplyCount(estate, &G) == supplyCount(estate, &O) - 1); //Verify supplyCount of estate reduced by one
	COMPARE(G.discardCount[1] == O.discardCount[1] + 1); //Verify discard count increased by one
	COMPARE(G.discard[1][0] == estate); //Verify estate placed in discard
	
	
	//TEST 6: Do not discard estate with estate supply == 0
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand count and composition
	G.handCount[1] = handCount;

	//Set supply counts
	G.supplyCount[estate] = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	baronEffect(0, 1, &G);

	//Verify no relevant changes to game state
	COMPARE(supplyCount(estate, &G) == 0); //Verify supplyCount of estate still 0
	COMPARE(G.discardCount[1] == O.discardCount[1]); //Verify discard count unchanged
	COMPARE(G.discard[1][0] != estate); //Verify estate not in discard pile
	
	printf("Finished Testing Baron\n\n\n");
}
