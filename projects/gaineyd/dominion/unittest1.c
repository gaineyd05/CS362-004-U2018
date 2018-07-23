#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkGainCard(int supplyPos, int player, struct gameState *post, int gainLoc) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int startSupply = post->supplyCount[supplyPos];
    
    int r;
    r = gainCard(supplyPos, post, gainLoc, player);
    
    // Make necessary changes for test
    if(pre.supplyCount[supplyPos] > 0) {
        pre.supplyCount[supplyPos]--;
        if(gainLoc == 0)
            pre.discardCount[player]++;
        else if(gainLoc == 1)
            pre.deckCount[player]++;
        else
            pre.handCount[player]++;
    }
        
        
    if(r==0 && startSupply == 0) {
        printf("TEST FAILED          Player: %d, card: %d, gainedWhere: %d\n",player, supplyPos, gainLoc);
        return -1;
    } else if(r==1 && startSupply > 0) {
        printf("TEST FAILED          Player: %d, card: %d, gainedWhere: %d\n",player, supplyPos, gainLoc);
        return -1;
    } else if(pre.deckCount[player] != post->deckCount[player] || pre.discardCount[player] != post->discardCount[player] || pre.handCount[player] != post->handCount[player]
       || pre.supplyCount[supplyPos] != post->supplyCount[supplyPos]) {
        printf("TEST FAILED          Player: %d, card: %d, gainedWhere: %d\n",player, supplyPos, gainLoc);
        return -1;
    } else {
        // printf("TEST OK\n");
        return 0;
    }
}

// Tests whether gain card function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, x, gainLoc, deckCount, discardCount, handCount, suppCount, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing gainCard.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    // External for loops are very similar to provided example
    // Check for both players
    for(p = 0; p < 2; p++) {
        // Check when cards are and are not present in deck, discard, hand
        for(deckCount = 0; deckCount < 10; deckCount++) {
            for(discardCount = 0; discardCount < 10; discardCount++) {
                // Check up to high values for hand
                for(handCount = 0; handCount < 10; handCount++) {
                    // Check for gains to deck, hand, and discard
                    for(gainLoc = 0; gainLoc < 3; gainLoc++) {
                        
                        // Check for all supplied cards
                        for(x = 0; x < 10; x++) {
                            // Setup code originally from testBuyCard.c
                            memset(&G, 23, sizeof(struct gameState));
                            initializeGame(2, k, 1, &G);
                            G.deckCount[p] = deckCount;
                            memset(G.deck[p], 0, sizeof(int) * deckCount);
                            G.discardCount[p] = discardCount;
                            memset(G.discard[p], 0, sizeof(int) * discardCount);
                            G.handCount[p] = handCount;
                            memset(G.hand[p], 0, sizeof(int) * handCount);
                        
                            G.supplyCount[k[x]] = 10;
                            // Check when cards are in/out of supplyPos via repetition
                            for(suppCount = 10; suppCount >= 0; suppCount--) {
                                testVal = checkGainCard(k[x],p,&G,gainLoc);
                                if(testVal == -1)
                                    testsOk = 0;
                            }
                        
                        }
                    }
                    
                }
            }
        }
    }
    if(testsOk)
        printf("ALL TESTS OK\n");
    return 0;
}
