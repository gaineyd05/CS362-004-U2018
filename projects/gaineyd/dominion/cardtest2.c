#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkFeast(int player, struct gameState *post, int choice, int currSupply) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    feastCard(post, choice);
    
    if(getCost(choice) < 6 && currSupply > 0)
        pre.supplyCount[choice]--;
    
    
    if(supplyCount(choice,&pre) != supplyCount(choice,post)) {
        printf("TEST FAILED          Player: %d, Current Supply: %d, Choice: %d, Choice Cost: %d\n",player, currSupply, choice, getCost(choice));
        return -1;
    } else {
        printf("TEST OK          Player: %d, Current Supply: %d, Choice: %d, Choice Cost: %d\n",player, currSupply, choice, getCost(choice));
        return 0;
    }
}

// Tests whether feast card function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, x, handCount, currSupply, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing feastCard.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    // External for loops are very similar to provided example
    // Check for both players
    for(p = 0; p < 2; p++) {
        // Check for all kingdom cards
        for(x = 0; x < 10; x++) {
            // Check for different hand sizes
            for(handCount = 1; handCount < 10; handCount++) {
                
                // Setup code originally from testBuyCard.c
                memset(&G, 23, sizeof(struct gameState));
                initializeGame(2, k, 1, &G);
                G.handCount[p] = handCount;
                memset(G.hand[p], 0, sizeof(int) * handCount);
                G.whoseTurn = p;
                G.supplyCount[k[x]] = 10;
                
                for(currSupply = 10; currSupply >= 0; currSupply--) {
                    testVal = checkFeast(p,&G, k[x], currSupply);
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
