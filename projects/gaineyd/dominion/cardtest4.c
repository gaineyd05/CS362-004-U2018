#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkAdventurer(int player, struct gameState *post, int deckSize, int discardSize, int c) {
    // printf("hi\n");
    adventurerCard(post);
    // printf("bye\n");
    updateCoins(player,post,0);
    
    if((c = 0 && post->coins != 1) || (c = 1 && post->coins != 2) || (c = 2 && post->coins != 3) || (c = 3 && post->coins != 4)) {
        printf("TEST FAILED          Player: %d, Case: %d, Expected Coins: %d, Actual Coins: %d, Deck Size: %d, Discard Size: %d\n",player, c, (c + 1), post->coins, deckSize, discardSize);
        return -1;
    } else {
        printf("OK                   Player: %d, Case: %d, Expected Coins: %d, Actual Coins: %d, Deck Size: %d, Discard Size: %d\n",player, c, (c + 1), post->coins, deckSize, discardSize);
        return 0;
    }
    
}

// Tests whether adventurer card function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, c, deckCount, handCount, discardCount, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing adventurerCard.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    // Test numCards drawn
    //
    
    int testsOk = 1;
    // External for loops are very similar to provided example
    // Check for both players
    for(p = 0; p < 2; p++) {
        // Check when cards are present in deck
        for(deckCount = 4; deckCount < 10; deckCount++) {
            // Check for different hand sizes
            for(handCount = 1; handCount < 10; handCount++) {
                // Check for different hand positions
                for(discardCount = 4; discardCount < 10; discardCount++) {
                        // Setup code originally from testBuyCard.c
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(2, k, 1, &G);
                        G.deckCount[p] = deckCount;
                        memset(G.deck[p], 0, sizeof(int) * deckCount);
                        G.discardCount[p] = discardCount;
                        memset(G.discard[p], 0, sizeof(int) * discardCount);
                        G.handCount[p] = handCount;
                        memset(G.hand[p], 0, sizeof(int) * handCount);
                        G.whoseTurn = p;
                        
                        for(c = 0; c < 3; c++) {
                            // Case 0: 1 Treasure total, from discard
                            if(c == 0)
                                memset(G.discard[p], copper, sizeof(int));
                            // Case 1: Treasures all come from discard
                            else if(c == 1) {
                                memset(G.deck[p], copper, sizeof(int) * 2);
                                // Case 2: 1 Treasure from each deck and discard
                            } else if(c == 2) {
                                memset(G.deck[p], copper, sizeof(int));
                                memset(G.discard[p], silver, sizeof(int));
                                // Case 3: Treasures all come from deck
                            } else if(c == 3) {
                                memset(G.deck[p], silver, sizeof(int) * 2);
                                memset(G.discard[p], gold, sizeof(int) * discardCount);
                            }
                            testVal = checkAdventurer(p,&G, deckCount, discardCount, c);
                            if(testVal == -1)
                                testsOk = 0;
                        }
                }
            }
        }
    }
    if(testsOk)
        printf("ALL TESTS OK\n");
    return 0;
}
