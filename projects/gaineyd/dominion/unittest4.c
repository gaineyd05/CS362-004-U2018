#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkfullDeckCount(int player, int card, struct gameState *post, int fullCount) {
    int r;
    r = fullDeckCount(player, card, post);
    
    if(r != fullCount) {
        printf("TEST FAILED          Player: %d, Card: %d, Expected Number: %d, Actual Number: %d\n", player, card, fullCount, r);
        return -1;
    } else {
        // printf("OK          Player: %d, Card: %d, Expected Number: %d, Actual Number: %d\n", player, card, fullCount, r);
        return 0;
    }
}

// Tests whether fullDeckCount function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, handSize, deckSize, discardSize, fullSize, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing fullDeckCount.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    // Check for all players
    for(p = 0; p < 2; p++) {
        // Check for all hand, deck, and discard sizes between 1 and 10
        for(handSize = 0; handSize < 10; handSize++) {
            for(deckSize = 0; deckSize < 10; deckSize++) {
                for(discardSize = 0; discardSize < 10; discardSize++) {
                        // Initial setup code from provided examples
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(2, k, 1, &G);
                        G.deckCount[p] = deckSize;
                        memset(G.deck[p], 0, sizeof(int) * deckSize);
                        G.discardCount[p] = discardSize;
                        memset(G.discard[p], 0, sizeof(int) * discardSize);
                        G.handCount[p] = handSize;
                        memset(G.hand[p], 0, sizeof(int) * handSize);
                        
                        fullSize = handSize + deckSize + discardSize;
                        // Check for all modulus values
                        
                        testVal = checkfullDeckCount(p, 0, &G, fullSize);
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
