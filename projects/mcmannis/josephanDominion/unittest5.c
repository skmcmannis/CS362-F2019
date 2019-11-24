//Unit Test 5 - Mine
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
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, tribute, great_hall};

	//Declare game states
	struct gameState G;
	struct gameState O;

	//Delcare random seed
	int seed = time(NULL);

	printf("\n\nBegin Testing Mine:\n");

	//TEST 1: Trash a treasure card and gain the same treasure card
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	int r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	int ret = mineCardEffect(0, 1, copper, 0, &G, 0, 0, 0);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.playedCards[0] == mine); //Verify mine in played card pile
	COMPARE(G.playedCards[1] == copper); //Verify copper in played card pile
	COMPARE(G.playedCardCount == O.playedCardCount + 2); //Verify played card count increase by 2
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count reduced by one
	COMPARE(G.hand[0][0] == copper); //Verify copper in hand


	//TEST 2: Trash a non-treasure card
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = baron;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = mineCardEffect(0, 1, copper, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 3: Trash a treasure card and return a non-treasure card
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = silver;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = mineCardEffect(0, 1, baron, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 4: Trash a treasure card and return a treasure card that is too expensive
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = mineCardEffect(0, 1, gold, 0, &G, 0, 0, 0);

	COMPARE(ret == -1); //Verify return value = -1 (failure)


	//TEST 5: Trash a treasure card and gain an affordable treasure card
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = mineCardEffect(0, 1, silver, 0, &G, 0, 0, 0);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.playedCards[0] == mine); //Verify mine in played card pile
	COMPARE(G.playedCards[1] == copper); //Verify copper in played card pile
	COMPARE(G.playedCardCount == O.playedCardCount + 2); //Verify played card count increase by 2
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count reduced by one
	COMPARE(G.hand[0][0] == silver); //Verify silver in hand


	//TEST 6: Trash a treasure card (with three in hand) and gain an affordable treasure card
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 4;
	G.hand[0][0] = mine;
	G.hand[0][1] = copper;
	G.hand[0][2] = copper;
	G.hand[0][3] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = mineCardEffect(0, 1, silver, 0, &G, 0, 0, 0);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.playedCards[0] == mine); //Verify mine in played card pile
	COMPARE(G.playedCards[1] == copper); //Verify copper in played card pile
	COMPARE(G.playedCardCount == O.playedCardCount + 2); //Verify played card count increase by 2
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count reduced by one
	COMPARE(G.hand[0][0] == silver); //Verify silver in hand


	printf("Finished Testing Mine\n\n\n");
}
