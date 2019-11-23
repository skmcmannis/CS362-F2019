//Unit Test 4 - Tribute
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

	printf("\n\nBegin Testing Tribute:\n");

	//TEST 1: Next player reveals two different treasure cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	int r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 2;
	G.deck[1][0] = copper;
	G.deck[1][1] = silver;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	int ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.deckCount[1] == O.deckCount[1] - 2); //Verify two cards removed from next player's deck
	COMPARE(G.discardCount[1] == O.discardCount[1] + 2); //Verify two cards added to discard pile
	COMPARE(G.discard[1][0] == copper); //Verify copper discarded
	COMPARE(G.discard[1][1] == silver); //Verify silver discarded
	COMPARE(G.coins == O.coins + 4); //Verify coins increase by 4


	//TEST 2: Next player reveals two identical treasure cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 2;
	G.deck[1][0] = copper;
	G.deck[1][1] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.deckCount[1] == O.deckCount[1] - 2); //Verify two cards removed from next player's deck
	COMPARE(G.coins == O.coins + 2); //Verify coins increase by 2


	//TEST 3: Next player reveals two different victory cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 2;
	G.deck[1][0] = estate;
	G.deck[1][1] = duchy;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.deckCount[1] == O.deckCount[1] - 2); //Verify two cards removed from next player's deck
	COMPARE(G.handCount[0] == O.handCount[0] + 3); //Verify hand count increased by 3
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile


	//TEST 4: Next player reveals two indentical victory cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 2;
	G.deck[1][0] = estate;
	G.deck[1][1] = estate;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.deckCount[1] == O.deckCount[1] - 2); //Verify two cards removed from next player's deck
	COMPARE(G.handCount[0] == O.handCount[0] + 1); //Verify hand count increased by 1
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile


	//TEST 5: Next player reveals two different action cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 2;
	G.deck[1][0] = ambassador;
	G.deck[1][1] = baron;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.deckCount[1] == O.deckCount[1] - 2); //Verify two cards removed from next player's deck
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count decreased by 1
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile
	COMPARE(G.numActions == O.numActions + 4); //Verify actions incrased by 4


	//TEST 6: Next player reveals two indentical action cards
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 2;
	G.deck[1][0] = ambassador;
	G.deck[1][1] = ambassador;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.deckCount[1] == O.deckCount[1] - 2); //Verify two cards removed from next player's deck
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count decreased by 1
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile
	COMPARE(G.numActions == O.numActions + 2); //Verify actions incrased by 2


	//TEST 7: Next player has one card in deck and one in discard
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 1;
	G.deck[1][0] = copper;
	
	//Set next player's discard variables
	G.discardCount[1] = 1;
	G.discard[1][0] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count decreased by 1
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile
	COMPARE(G.deckCount[1] == O.deckCount[1] - 1); //Verify next player's deck count reduced by 1
	COMPARE(G.discardCount[1] == O.discardCount[1] - 1); //Verify next player's discard count reduced by 1


	//TEST 8: Next player has one card in deck and none in discard
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 1;
	G.deck[1][0] = copper;
	
	//Set next player's discard variables
	G.discardCount[1] = 0;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count decreased by 1
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile
	COMPARE(G.deckCount[1] == O.deckCount[1] - 1); //Verify next player's deck count reduced by 1


	//TEST 9: Next player has one card in discard and none in deck
	//Set game states
	memset(&G, 23, sizeof(struct gameState));
	memset(&O, 23, sizeof(struct gameState));

	//Initialize a new game
	r = initializeGame(2, k, seed, &G);

	//Set hand variables
	G.handCount[0] = 1;
	G.hand[0][0] = tribute;

	//Set next player's deck variables
	G.deckCount[1] = 0;
	
	//Set next player's discard variables
	G.discardCount[1] = 1;
	G.discard[1][0] = copper;

	//Copy current game state
	memcpy(&O, &G, sizeof(struct gameState));

	//Call the function
	ret = tributeEffect(0, 1, &G);

	COMPARE(ret == 0); //Verify return value = 0 (success)
	COMPARE(G.handCount[0] == O.handCount[0] - 1); //Verify hand count decreased by 1
	COMPARE(G.playedCardCount == O.playedCardCount + 1); //Verify played card count increased by 1
	COMPARE(G.playedCards[0] == tribute); //Verify tribute in played cards pile
	COMPARE(G.discardCount[1] == O.discardCount[1] - 1); //Verify next player's discard count reduced by 1


	printf("Finished Testing Tribute\n\n\n");
}
