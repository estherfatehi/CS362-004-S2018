#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    struct gameState *G;
    
	G = newGame();
	
	if (G != NULL) { 
		printf("newGame(): PASS when new game successfully malloc'ed in memory\n"); 
	}
	else { printf("newGame(): FAIL when new game is null in memory\n"); }

    return 0;
}