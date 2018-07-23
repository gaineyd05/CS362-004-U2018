#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkCouncilRoom(int player, struct gameState *post, int handPos) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int player2 = (player + 1) % 2;
    
    councilRoomCard(post, handPos);
    
    pre.numBuys++;
    pre.handCount[player] = pre.handCount[player] + 3;
    pre.handCount[player2] = pre.handCount[player2] + 1;
    
    if(pre.handCount[player] != post->handCount[player] || pre.handCount[player2] != post->handCount[player2]) {
        printf("TEST FAILED          Player: %d, Hand Pos: %d, Player1Hand: %d, Player2Hand: %d\n",player, handPos, pre.handCount[player] - 3, pre.handCount[player2] - 1);
        return -1;
    } else {
        return 0;
    }
}

// Tests whether council room card function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int p, p2, handCount1, handCount2, nBuys, handPos, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing councilRoomCard.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    // External for loops are very similar to provided example
    // Check for both players
    for(p = 0; p < 2; p++) {
        // p2 = other player
        p2 = (p + 1) % 2;
        // Check for different hand sizes for player 1
        for(handCount1 = 1; handCount1 < 10; handCount1++) {
            // Check for different hand sizes for player 2
            for(handCount2 = 1; handCount2 < 10; handCount2++) {
                for(nBuys = 1; nBuys < 5; nBuys++) {
                    for(handPos = 0; handPos < handCount1; handPos++) {
                        // Setup code originally from testBuyCard.c
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(2, k, 1, &G);
                        G.handCount[p] = handCount1;
                        memset(G.hand[p], 0, sizeof(int) * handCount1);
                        G.handCount[p2] = handCount2;
                        memset(G.hand[p2], 0, sizeof(int) * handCount2);
                        G.whoseTurn = p;
                        G.numBuys = nBuys;
                        
                        testVal = checkCouncilRoom(p,&G,handPos);
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
