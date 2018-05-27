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
	int newCards = 0, newActions = 0, handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int discarded = 1;
	int numPlayers = 2;
	int thisPlayer = 0;   
	int nextPlayer = 1;
	int seed = 1000;
	int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int i;
	int flag = 0;
	int playerFlag = 0;
	int treasures = 0;
	
	int number = 0;
	
	//start a new game
	initializeGame(numPlayers, k, seed, &G);
	
	//make a test game
	memcpy(&testG, &G, sizeof(struct gameState));

	//change player's first card to adventurer
	testG.hand[thisPlayer][0] = k[0];
	
	for (i = 1; i <= 4; i++) {
		testG.hand[thisPlayer][i] = number;
		number++;
	}
	
	number = 4;
	for (i = 0; i < 3; i++) {
		testG.deck[thisPlayer][i] = number;
		number++;
	}
	
	testG.deck[thisPlayer][3] = 10;
	testG.deck[thisPlayer][4] = 11;
	
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	//test that two treasures were drawn
	for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		if ((testG.hand[thisPlayer][i] == copper) || (testG.hand[thisPlayer][i] == silver) || (testG.hand[thisPlayer][i] == gold)) {
			treasures++;
		}
	}
	if (treasures == 2) {
		printf("PASS: total number of treasures in hand = 2\n");
	}
	else {
		printf("FAIL: total number of treasures in hand does not equal 2\n");
	}
	
	//test that adventurer is no longer in the deck/hand
	for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == 14) {
			printf("FAIL: adventurer card is still in hand\n");
			printf("printing %d in hand\n", i);
			flag = 1;
			break;
		}
	}
	for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == 14) {
			printf("FAIL: adventurer card is still in deck\n");
			flag = 1;
			break;
		}
	}
	if (flag == 0) { printf("PASS: adventurer is no longer in either hand or deck\n"); }
	
	//test that nothing changed for the other player
	for (i = 0; i < testG.handCount[nextPlayer]; i++) {
		if (testG.hand[nextPlayer][i] != (G.hand[nextPlayer][i])) {
			printf("FAIL: nextPlayer state has changed\n");
			playerFlag = 1;
			break;
		}
	}
	for (i = 0; i < testG.deckCount[nextPlayer]; i++) {
		if (testG.deck[nextPlayer][i] != (G.deck[nextPlayer][i])) {
			printf("FAIL: nextPlayer state has changed\n");
			playerFlag = 1;
			break;
		}
	}
	if (playerFlag == 0) { printf("PASS: nextPlayer state has not changed\n"); }
	
    return 0;
}