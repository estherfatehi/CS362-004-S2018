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
	int discarded = 1;
	int numPlayers = 2;
	int thisPlayer = 0;   
	int nextPlayer = 1;
	int seed = 1000;
	int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};
	int i;
	int flag = 0;
	int playerFlag = 0;
	int great_hall = 16;
	
	//start a new game
	initializeGame(numPlayers, k, seed, &G);
	
	//make a test game
	memcpy(&testG, &G, sizeof(struct gameState));

	//change player's first card to great_hall
	testG.hand[thisPlayer][0] = k[1];

	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 1;
	newActions = 1;
	
	//test that hand count matches
	if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded) {
		printf("PASS: test hand count %d = expected hand count %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	}
	else { printf("FAIL: test hand count %d != expected hand count %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded); }
	
	//test that deck count matches
	if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards) {
		printf("PASS: test deck count %d = expected deck count %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	}
	else { printf("FAIL: test deck count %d != expected deck count %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards); }
	
	//test that action numbers matches
	if (testG.numActions == G.numActions + newActions) {
		printf("PASS: expected action count %d = test action count %d\n", testG.numActions, G.numActions + newActions);
	}
	else { printf("FAIL: expected action count != test action count\n"); }
	
	//test that the card played was the correct card
	if (testG.playedCards[0] == great_hall) {
		printf("PASS: great_hall card is in the played pile\n");
	}
	else {
		printf("FAIL: great_hall card is not in the played pile\n");
	}
	
	//test that great_hall is no longer in the deck/hand
	for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		if (testG.hand[thisPlayer][i] == 14) {
			printf("FAIL: great_hall card is still in hand\n");
			flag = 1;
			break;
		}
	}
	for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
		if (testG.deck[thisPlayer][i] == 14) {
			printf("FAIL: great_hall card is still in deck\n");
			flag = 1;
			break;
		}
	}
	if (flag == 0) { printf("PASS: great_hall is no longer in either hand or deck\n"); }
	
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