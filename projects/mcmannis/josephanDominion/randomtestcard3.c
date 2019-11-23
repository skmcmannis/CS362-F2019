//Random Test 3 - Tribute
//Author: Shawn McMannis
//CS 362 Software Engineering II
//Last Mod Date: 11/15/2019

#include "dominion.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Return hand size between 1 and 10, inclusive
int randHandCount()
{
	int h = 1 + rand() / (RAND_MAX / (10 - 1 + 1) + 1);
	return h;
}


//Returns 0-10
int randCount()
{
	int h = 0 + rand() / (RAND_MAX / (10 - 0 + 1) + 1);
	return h;
}


//Return card between estate and great_hall, inclusive
int randCard()
{
	int c = 1 + rand() / (RAND_MAX / (16 - 1 + 1) + 1);
	return c;
}


//Retern either 0 or 1
int binary()
{
	int c = 0 + rand() / (RAND_MAX / (1 - 0 + 1) + 1);
	return c;
}


int runTest()
{
	int testCount = 0;
	int cards[2] = {-1, -1};
	int i;
	int treasures;
	int victory;
	int actions;

	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Declare game st:ates
	struct gameState G;
	struct gameState O;

	//Delcare random seed
	int seed = time(NULL);

	printf("***BEGIN TESTING TRIBUTE***\n\n");

	while(testCount < 500)
	{
		//Reset variables
		cards[0] = -1;
		cards[1] = -1;
		treasures = 0;
		victory = 0;
		actions = 0;

		//Set game states
		memset(&G, 23, sizeof(struct gameState));
		memset(&O, 23, sizeof(struct gameState));

		//Initialize a new game
		int r = initializeGame(2, k, seed, &G);

		//Set hand variables
		G.handCount[0] = randHandCount();
		G.hand[0][0] = tribute;

		//Set next player deck variables
		G.deckCount[1] = randCount();
		for(int i = 0; i < G.deckCount[1]; i++)
		{
			G.deck[1][i] = randCard();
		}
		G.discardCount[1] = randCount();
		for(int j = 0; j < G.discardCount[1]; j++)
		{
			G.discard[1][j] = randCard();
		}

		//Copy current game state
		memcpy(&O, &G, sizeof(struct gameState));

		//Call the function
		tributeEffect(0, 1, &G);

		testCount++;
		printf("Iteration %d\n", testCount);

		//Oracle
		
		COMPARE(G.playedCards[0] == tribute);

		if(O.deckCount[1] == 0 && O.discardCount[1] == 1)
		{
			COMPARE(G.discardCount[1] == O.discardCount[1] - 1);
			cards[0] = O.discard[1][0];
		}
		else if(O.deckCount[1] == 1 && O.discardCount[1] == 0)
		{
			COMPARE(G.deckCount[1] == O.deckCount[1] - 1);
			cards[0] = O.deck[1][0];
		}
		else if(O.deckCount[1] == 0 && O.discardCount[1] > 2)
		{
			COMPARE(G.discardCount[1] == 2);
			COMPARE(G.deckCount[1] == O.discardCount[1] - 2);
		}
		else if(O.deckCount[1] == 0 && O.discardCount[1] == 2)
		{
			COMPARE(G.deckCount[1] == 0);
			COMPARE(G.discardCount[1] == 2);
			cards[0] = O.discard[1][0];
			cards[1] = O.discard[1][1];
		}
		else if(O.deckCount[1] > 1)
		{
			COMPARE(G.deckCount[1] == O.deckCount[1] - 2);
			COMPARE(G.discardCount[1] == O.discardCount[1] + 2);
			cards[0] = O.deck[1][0];
			cards[1] = O.deck[1][1];
		}

		for(i = 0; i < 2; i++)
		{
			if(cards[i] == copper || cards[i] == silver || cards[i] == gold)
			{
				treasures += 2;
			}
			else if(cards[i] == estate || cards[i] == duchy || cards[i] == province || cards[i] == gardens || cards[i] == great_hall)
			{
				victory += 2;
			}
			else
			{
				actions += 2;
			}
		}

		COMPARE(G.coins == O.coins + treasures);
		COMPARE(G.handCount[0] == O.handCount[0] + victory);
		COMPARE(G.numActions == O.numActions + actions);

		printf("\n\n");
	}

	printf("***FINISHED TESTING TRIBUTE***\n\n");

	return 0;
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	runTest();
	return 0;
}
