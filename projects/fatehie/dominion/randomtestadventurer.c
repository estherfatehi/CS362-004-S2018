#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

//testing adventurer card
int main() {
    struct gameState G, testG;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int pass = 0, fail = 0;
	int numPlayers = 2;
	int thisPlayer = 0;   
	int seed = 1000;
	int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int i, x;
	int treasures = 0;
		
	for (x = 0; x < 1000000; x++) {
		//start a new game
		initializeGame(numPlayers, k, seed, &G);
		
		//make a test game
		memcpy(&testG, &G, sizeof(struct gameState));

		//change player's first card to adventurer
		testG.hand[thisPlayer][0] = k[0];
		
		//randomize number of players -- limit is from 0 to 10
		testG.numPlayers = rand() % 11;
		//randomize hand position -- limit it to player's hand count
		handpos = rand() % (testG.handCount[thisPlayer] + 1);
		//randomize numActions -- range of 0 to 2
		testG.numActions = rand() % 3;
		//randomize numBuys -- range of 0 to 2
		testG.numBuys = rand() % 3;
		
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
		
		//test that two treasures were drawn
		for (i = 0; i < testG.handCount[thisPlayer]; i++) {
			if ((testG.hand[thisPlayer][i] == copper) || (testG.hand[thisPlayer][i] == silver) || (testG.hand[thisPlayer][i] == gold)) {
				treasures++;
			}
		}
		if (treasures == 2) {
			pass++;
		}
		else {
			fail++;
		}
		

	}
	printf("Testing to see if two treasures were drawn...\n");
	printf("TOTAL PASS: %d\nTOTAL FAIL: %d\n", pass, fail);
    return 0;
}