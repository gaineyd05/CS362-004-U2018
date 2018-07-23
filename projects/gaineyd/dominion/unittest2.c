#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkDiscardCard(int player, struct gameState *post, int handPos, int handSize, int trashed) {
    
    int r;
    r = discardCard(handPos, player, post, trashed);
    
    int stillHasCard = 0;
        if(post->hand[player][handPos] == 1){
            stillHasCard = 1;
        }
    
    
    int wrongHandCount = 0;
    if(post->handCount[player] - (handSize - 1) != 0)
        wrongHandCount = 1;
    
    if(r != 0) {
        printf("TEST FAILED          returned error, Player: %d, HandSize: %d, HandPos: %d, trashed: %d\n",player,handSize,handPos,trashed);
        return -1;
    } else if(stillHasCard || wrongHandCount) {
        printf("TEST FAILED          Player: %d, HandSize(Theor): %d, HandSize(Actual): %d, HandPos: %d, trashed: %d\n",player,(handSize - 1),post->handCount[player],handPos,trashed);
        return -1;
    } else {
        // printf("TEST OK\n");
        return 0;
    }
}

// Tests whether discard card function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, handPos, hCount, trashed, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing discardCard.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    
    // Check for both players
    for(p = 0; p < 2; p++) {
                // Check up to high values for hand
                for(hCount = 1; hCount < 10; hCount++) {
                    // Check for all hand positions
                    for(handPos = 0; handPos < hCount; handPos++) {
                        // Setup code originally from testBuyCard.c
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(2, k, 1, &G);
                        G.handCount[p] = hCount;
                        memset(G.hand[p], 0, sizeof(int) * hCount);
                        
                        // Set selected hand position to 1
                        // G.hand[p][handPos] = 1;
                        
                        for(trashed = 0; trashed < 2; trashed++) {
                            testVal = checkDiscardCard(p,&G,handPos, hCount, trashed);
                            if(testVal == -1)
                                testsOk = 0;
                        }
                    }
                    
                }
    }
    if(testsOk)
        printf("ALL TESTS OK\n");
    return 0;
}
