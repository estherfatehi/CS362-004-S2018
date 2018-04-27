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
	int i, r, x;
	
	G = newGame();
	r = initializeGame(2, k, seed, G); // initialize a new game
	
	x = isGameOver(G);
	
	if (x == 0) {
		printf("isGameOver(G): PASS when game is not over right after being initialized\n");
	}
	else {
		printf("isGameOver(G): FAIL when game is over right after being initialized\n");
	}
	
    return 0;
}