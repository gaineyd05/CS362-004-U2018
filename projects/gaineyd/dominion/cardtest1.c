#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkSmithy(int player, struct gameState *post, int handPos, int handSize, int deckSize) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    smithyCard(post, handPos);
    
    pre.deckCount[player] = pre.deckCount[player] - 3;
    pre.handCount[player] = pre.handCount[player] + 2;
    
    if(pre.handCount[player] != post->handCount[player]) {
        printf("TEST FAILED          Player: %d, Hand Size: %d, New Hand Size (Theor): %d, New Hand Size (Actual): %d, Deck Size: %d, Hand Position: %d\n",player, handSize,
               post->handCount[player], post->handCount[player], deckSize, handPos);
        return -1;
    } else {
        // printf("TEST OK\n");
        return 0;
    }
}

// Tests whether smithy card function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, deckCount, handCount, handPos, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing smithyCard.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    // External for loops are very similar to provided example
    // Check for both players
    for(p = 0; p < 2; p++) {
        // Check when cards are present in deck
        for(deckCount = 4; deckCount < 10; deckCount++) {
            // Check for different hand sizes
                for(handCount = 1; handCount < 10; handCount++) {
                    // Check for different hand positions
                    for(handPos = 0; handPos < handCount; handPos++) {
                        
                        // Setup code originally from testBuyCard.c
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(2, k, 1, &G);
                        G.deckCount[p] = deckCount;
                        memset(G.deck[p], 0, sizeof(int) * deckCount);
                        G.handCount[p] = handCount;
                        memset(G.hand[p], 0, sizeof(int) * handCount);
                        G.whoseTurn = p;
                    
                        testVal = checkSmithy(p,&G,handPos, handCount, deckCount);
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
