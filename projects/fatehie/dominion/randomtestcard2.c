#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

//testing great_hall card
int main() {
    struct gameState G, testG;
	int newCards = 0, newActions = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int testHandCount = 0, testDeckCount = 0, testActionCount = 0, testPlayed = 0;
	int failOne = 0, failTwo = 0, failThree = 0, failFour = 0;
	int totalPass = 0, totalFail = 0;
	int discarded = 1;
	int numPlayers = 2;
	int thisPlayer = 0;   
	int seed = 1000;
	int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int x;
	int great_hall = 16;
	
	for (x = 0; x < 1000000; x++) {
		//start a new game
		initializeGame(numPlayers, k, seed, &G);
		
		//make a test game
		memcpy(&testG, &G, sizeof(struct gameState));

		//change player's first card to great_hall
		testG.hand[thisPlayer][0] = k[1];
		
		//randomize number of players -- limit is from 0 to 10
		testG.numPlayers = rand() % 11;
		//randomize hand position -- limit it to player's hand count
		handpos = rand() % (testG.handCount[thisPlayer] + 1);
		//randomize numActions -- range of 0 to 2
		testG.numActions = rand() % 3;
		//randomize numBuys -- range of 0 to 2
		testG.numBuys = rand() % 3;

		cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
		newCards = 1;
		newActions = 1;
		
		//test that hand count matches
		if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded) {
			testHandCount++;
		}
		else { failOne++; }
		
		//test that deck count matches
		if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards) {
			testDeckCount++;
		}
		else { failTwo++; }
		
		//test that action numbers matches
		if (testG.numActions == G.numActions + newActions) {
			testActionCount++;
		}
		else { failThree++; }
		
		//test that the card played was the correct card
		if (testG.playedCards[0] == great_hall) {
			testPlayed++;
		}
		else {
			failFour++;
		}
	}
	
	totalPass = testHandCount + testDeckCount + testActionCount + testPlayed;
	totalFail = failOne + failTwo + failThree + failFour;
	printf("Testing that hand count matches. Passes: %d. Fails: %d.\n", testHandCount, failOne);
	printf("Testing that deck count matches. Passes: %d. Fails: %d.\n", testDeckCount, failTwo);
	printf("Testing that action count matches. Passes: %d. Fails: %d.\n", testActionCount, failThree);
	printf("Testing that correct card was played. Passes: %d. Fails: %d.\n", testPlayed, failFour);
	
	printf("TOTAL PASSES: %d\nTOTAL FAILS: %d\n", totalPass, totalFail);
	printf("RATIO OF PASSES TO FAILS: %lf\n", (double)totalPass/(double)totalFail);
	
    return 0;
}