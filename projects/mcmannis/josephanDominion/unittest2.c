//Unit Test 2 - Minion
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
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, minion, great_hall};

	//Declare game states
	struct gameState G;
	struct gameState O;

	//Delcare random seed
	int seed = time(NULL);

	printf("\n\nBegin Testing Minion:\n");

	//TEST 1: Choose to gain 2 coins
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	int r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = minion;
	G.hand[0][1] = estate;

	//Set current player
	G.whoseTurn = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	minionEffect(1, 0, 0, 0, &G);

	COMPARE(G.numActions == O.numActions + 1); //Verify addtional action granted
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count reduced by one
	COMPARE(G.hand[0][0] != minion); //Verify minion not in hand
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by one
	COMPARE(G.playedCards[0] == minion); //Verify minion in played card pile
	COMPARE(G.coins == O.coins + 2); //Verify 2 coins added


	//TEST 2: Choose to discard hand and next player's hand < 5
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.handCount[1] = 3;
	G.hand[0][0] = minion;
	G.hand[0][1] = estate;

	//Set current player
	G.whoseTurn = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	minionEffect(0, 1, 0, 0, &G);

	COMPARE(G.numActions == O.numActions + 1); //Verify addtional action granted
	COMPARE(G.handCount[0] == 4); //Verify hand count increased to 4
	COMPARE(G.playedCardCount == O.playedCardCount + 2); //Verify played count increased by two
	COMPARE(G.playedCards[0] == minion); //Verify minion in played pile
	COMPARE(G.handCount[1] == 3); //Verify next player hand size didn't change


	//TEST 3: Choose to gain 2 coins (adjusted for choice bug)
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.hand[0][0] = minion;
	G.hand[0][1] = estate;

	//Set current player
	G.whoseTurn = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	minionEffect(0, 1, 0, 0, &G);

	COMPARE(G.numActions == O.numActions + 1); //Verify addtional action granted
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count reduced by one
	COMPARE(G.hand[0][0] != minion); //Verify minion not in hand
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify discard count increased by one
	COMPARE(G.playedCards[0] == minion); //Verify only minion discarded
	COMPARE(G.coins == O.coins + 2); //Verify 2 coins added


	//TEST 4: Choose to discard hand and next player's hand < 5 (adjusted for choice bug)
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.handCount[1] = 3;
	G.hand[0][0] = minion;
	G.hand[0][1] = estate;

	//Set current player
	G.whoseTurn = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	minionEffect(1, 0, 0, 0, &G);

	COMPARE(G.numActions == O.numActions + 1); //Verify addtional action granted
	COMPARE(G.handCount[0] == 4); //Verify hand count increased to 4
	COMPARE(G.playedCardCount == O.playedCardCount + 2); //Verify played count increased by two
	COMPARE(G.playedCards[0] == minion); //Verify minion in played pile
	COMPARE(G.handCount[1] == 3); //Verify next player hand size didn't change


	//TEST 5: Choose to discard hand and next player's hand > 4 (adjusted for choice bug)
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 2;
	G.handCount[1] = 5;
	G.hand[0][0] = minion;
	G.hand[0][1] = estate;

	//Set current player
	G.whoseTurn = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	minionEffect(1, 0, 0, 0, &G);

	COMPARE(G.numActions == O.numActions + 1); //Verify addtional action granted
	COMPARE(G.handCount[0] == 4); //Verify hand count increased to 4
	COMPARE(G.playedCardCount == O.playedCardCount + 7); //Verify played count increased by 7
	COMPARE(G.playedCards[0] == minion); //Verify minion in played pile
	COMPARE(G.handCount[1] == 4); //Verify next player hand size reduced from 5 to 4


	//TEST 6: Choose to discard hand with only minion card in hand (adjusted for choice bug)
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = minion;

	//Set current player
	G.whoseTurn = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	minionEffect(1, 0, 0, 0, &G);

	COMPARE(G.numActions == O.numActions + 1); //Verify addtional action granted
	COMPARE(G.handCount[0] == 4); //Verify hand count increased to 4
	COMPARE(G.playedCardCount == O.playedCardCount + 6); //Verify played count increased by 6
	COMPARE(G.playedCards[0] == minion); //Verify minion in played pile
	COMPARE(G.handCount[1] == 4); //Verify next player hand size reduced from 5 to 4


	printf("Finished Testing Minion\n\n\n");
}
