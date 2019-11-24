//Unit Test 3 - Ambassador
//Author: Shawn McMannis
//CS 362 Software Engineering II
//Last Mod Date: 11/9/2019

#include "dominion.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, ambassador, great_hall};

	//Declare game states
	struct gameState G;
	struct gameState O;

	//Delcare random seed
	int seed = time(NULL);

	printf("\n\nBegin Testing Ambassador:\n");

	//TEST 1: Choose to discard less than 0 cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	int r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = ambassador;
	G.hand[0][1] = estate;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	int ret = ambassadorCardEffect(0, 1, -1, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 2: Choose to discard more than 2 cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = ambassador;
	G.hand[0][1] = estate;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = ambassadorCardEffect(0, 1, 3, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 3: Choose to discard the ambassador card
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = ambassador;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = ambassadorCardEffect(0, 0, 1, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 4: Choose to discard two cards when only one in hand
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = ambassador;
	G.hand[0][1] = estate;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = ambassadorCardEffect(0, 1, 2, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 5: Choose to discard two cards with two in hand
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 3;
	G.hand[0][0] = ambassador;
	G.hand[0][1] = estate;
	G.hand[0][2] = estate;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = ambassadorCardEffect(0, 1, 2, 0, &G, 0, 0, 0);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.supplyCount[estate] == O.supplyCount[estate] + 1); //Verify supply count for discarded card increased by 1
	COMPARE(G.discard[1][0] == estate); //Verify other player gained copy of discarded card
	COMPARE(G.handCount[0] == O.handCount[0] - 3); //Verify current player hand count reduced by 3
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == ambassador); //Verify ambassador card in played cards pile


	//TEST 6: Choose to discard two cards with three in hand
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 4;
	G.hand[0][0] = ambassador;
	G.hand[0][1] = estate;
	G.hand[0][2] = estate;
	G.hand[0][3] = estate;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = ambassadorCardEffect(0, 1, 2, 0, &G, 0, 0, 0);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.supplyCount[estate] == O.supplyCount[estate] + 1); //Verify supply count for discarded card increased by 1
	COMPARE(G.discard[1][0] == estate); //Verify other player gained copy of discarded card
	COMPARE(G.handCount[0] == O.handCount[0] - 3); //Verify current player hand count reduced by 3
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == ambassador); //Verify ambassador card in played cards pile

	printf("Finished Testing Ambassador\n\n\n");
}
