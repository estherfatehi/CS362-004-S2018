#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    struct gameState *G;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int i, r, x, deckCount;
	int flag = 0;
    int player = 1;
	
	G = newGame();
	r = initializeGame(2, k, seed, G); // initialize a new game
	
	deckCount = G->deckCount[player];
	int shuffleArray[deckCount];
	
	//put deck into an array
	for(i = 0; i < deckCount; i++) {
		shuffleArray[i] = G->deck[player][i];
	}

	//shuffle deck
	x = shuffle(player, G);
		
	//confirm that deck has been shuffled properly	
	for(i = 0; i < deckCount; i++) {
		if (G->deck[player][i] != shuffleArray[i]) {
			flag = 1;
			printf("shuffle(player, G): PASS when cards are shuffled\n");
			break;
		}
	}
	
	if (flag == 0) {
		printf("shuffle(player, G): FAIL when cards have not been shuffled\n");
	}
	
    return 0;
}