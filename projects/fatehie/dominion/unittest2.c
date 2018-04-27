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
	int r, x, y, z;
    
	G = newGame();
	r = initializeGame(2, k, seed, G); // initialize a new game
	
	//x is player 0
	x = whoseTurn(G);
	//end player 0's turn
	z = endTurn(G);
	//now y is player 1
	y = whoseTurn(G);
	if (x == 0) {
		printf("whoseTurn(G): PASS when game starts with player 0's turn\n");
		if (y == 1) {
			printf("endTurn(G) + whoseTurn(G): PASS when player turn switches to player 1\n");
		}
	}
	else { printf("whoseTurn(G) + endTurn(G) + whoseTurn(G): FAIL when player turn doesn't switch\n"); }

    return 0;
}