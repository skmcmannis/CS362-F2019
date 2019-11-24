//Random Test 2 - Minion
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
int binary()
{
	int c = 0 + rand() / (RAND_MAX / (1 - 0 + 1) + 1);
	return c;
}


//Reterns 2-4
int randNumPlayers()
{
	int c = 2 + rand() / (RAND_MAX / (4 - 2 + 1) + 1);
	return c;
}


int runTest()
{
	int testCount = 0;
	int choice1;
	int choice2;
	int numPlayers;
	int totalCards = 0;
	int i;
	int j;

	//Set card array
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//Declare game states
	struct gameState G;
	struct gameState O;

	//Delcare random seed
	int seed = time(NULL);

	printf("***BEGIN TESTING MINION***\n\n");

	while(testCount < 500)
	{
		//Reset total cards
		totalCards = 0;

		numPlayers = randNumPlayers();
		choice1 = binary();
		choice2 = binary();

		//Set game states
		memset(&G, 23, sizeof(struct gameState));
		memset(&O, 23, sizeof(struct gameState));

		//Initialize a new game
		int r = initializeGame(numPlayers, k, seed, &G);

		//Set hand variables
		G.handCount[0] = randHandCount();
		G.hand[0][0] = minion;
		for(j = 0; j < numPlayers; j++)
		{
			G.handCount[j] = randHandCount();
			for(i = 1; i < G.handCount[j]; i++)
			{
				G.hand[j][i] = randCard();
			}
		}

		//Copy current game state
		memcpy(&O, &G, sizeof(struct gameState));

		//Call the function
		minionCardEffect(0, choice1, choice2, 0, &G, 0, 0, 0);

		testCount++;
		printf("Iteration %d: choice1 = %d, choice2 = %d\n", testCount, choice1, choice2);

		//Oracle
		COMPARE(G.numActions == O.numActions + 1);
		COMPARE(G.playedCards[0] == minion);
		totalCards++;

		if(choice1 == 1 && choice2 == 0)
		{
			COMPARE(G.coins == O.coins + 2);
			COMPARE(G.hand[0][O.handCount[0]] == -1);
			COMPARE(G.handCount[0] == O.handCount[0] - 1);
			COMPARE(G.playedCardCount == O.playedCardCount + 1);
		}

		if(choice2 == 1)
		{
			COMPARE(G.handCount[0] == 4);
			totalCards += O.handCount[0];

			for(i = 1; i < numPlayers; i++)
			{
				if(O.handCount[i] > 4)
				{
					COMPARE(G.handCount[i] == 4);
					totalCards += O.handCount[i];
				}
				else
				{
					COMPARE(G.handCount[i] == O.handCount[i]);
				}
			}

			COMPARE(G.playedCardCount == totalCards);
		}

		printf("\n\n");
	}
	printf("***FINISHED TESTING MINION***\n\n");

	return 0;
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	runTest();
	return 0;
}
