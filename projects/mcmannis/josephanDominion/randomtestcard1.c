//Random Test 1 - Baron
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


//Return card between estate and great_hall, inclusive
int randCard()
{
	int c = 1 + rand() / (RAND_MAX / (16 - 1 + 1) + 1);
	return c;
}


//Retern either 0 or 1
int choice1()
{
	int c = 0 + rand() / (RAND_MAX / (1 - 0 + 1) + 1);
	return c;
}


int runTest()
{
	int testCount = 0;
	int handCount;
	int hasEstate;
	int choice;
	int estateCount;

	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Declare game states
	struct gameState G;
	struct gameState O;

	//Delcare random seed
	int seed = time(NULL);

	printf("***BEGIN TESTING BARON***\n\n");

	while(testCount < 500)
	{
		handCount = randHandCount();
		choice = choice1();
		hasEstate = 0;
		estateCount = choice1();

		//Set game states
		memset(&G, 23, sizeof(struct gameState));
		memset(&O, 23, sizeof(struct gameState));

		//Initialize a new game
		int r = initializeGame(2, k, seed, &G);

		//Set hand variables
		G.handCount[0] = handCount;
		G.hand[0][0] = baron;
		for(int i = 1; i < G.handCount[0]; i++)
		{
			G.hand[0][i] = randCard();
			if(G.hand[0][i] == estate)
			{
				hasEstate = 1;
			}
		}

		//Set estate supply
		G.supplyCount[estate] = estateCount;

		//Copy current game state
		memcpy(&O, &G, sizeof(struct gameState));

		//Call the function
		baronCardEffect(0, choice, 0, 0, &G, 0, 0, 0);

		testCount++;
		printf("Iteration %d: choice = %d, handCount = %d, hasEstate = %d, estateCount = %d\n", testCount, choice, handCount, hasEstate, estateCount);

		//Oracle
		COMPARE(G.numBuys == O.numBuys + 1);

		if(choice == 0 && estateCount == 1)
		{
			COMPARE(G.discard[0][0] == estate);
			COMPARE(G.supplyCount[estate] == O.supplyCount[estate] - 1);
		}

		COMPARE(G.playedCards[0] == baron);
		
		if(choice == 1 && hasEstate == 1)
		{
			COMPARE(G.coins == O.coins + 4);
			COMPARE(G.discard[0][0] == estate);
			COMPARE(G.discardCount == O.discardCount + 1);
			COMPARE(G.hand[0][handCount] == -1);
			COMPARE(G.handCount[0] == O.handCount[0] - 1);
		}

		if(choice == 1 && hasEstate == 0 && estateCount > 0)
		{
			COMPARE(G.discard[0][0] == estate);
			COMPARE(G.supplyCount[estate] == O.supplyCount[estate] - 1);
		}

		printf("\n\n");
	}

	printf("***FINISHED TESTING BARON***\n\n");

	return 0;
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	runTest();
	return 0;
}
