#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

// checkSmithy is identical to that written in Assignment 3 (cardtest1.c)
int checkSmithy(int player, struct gameState *post, int handPos, int handSize, int deckSize) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    smithyCard(post, handPos);
    
    pre.deckCount[player] = pre.deckCount[player] - 3;
    pre.handCount[player] = pre.handCount[player] + 2;
    
    if(pre.handCount[player] != post->handCount[player]) {
        // printf("TEST FAILED          Player: %d, Hand Size: %d, New Hand Size (Theor): %d, New Hand Size (Actual): %d, Deck Size: %d, Hand Position: %d\n",player, handSize,
        //       pre.handCount[player], post->handCount[player], deckSize, handPos);
        return -1;
    } else {
        // printf("TEST OK\n");
        return 0;
    }
}

// TESTS SMITHY CARD
int main(int argc, const char * argv[]) {
    int n, i, p, handPos, handSize, deckSize, discardSize;
    int testsOk, testVal, failCounter;
    struct gameState G;
    
    printf ("Testing smithyCard.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    testsOk = 1;
    failCounter = 0;
    // Much of setup of randomized gameState is based on provided example.
    for(n = 0; n < 20000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        
        p = floor(Random() * 2);
        G.whoseTurn = p;
        handSize = G.handCount[p] = floor(Random() * MAX_HAND);
        deckSize = G.deckCount[p] = floor(Random() * MAX_DECK);
        discardSize = G.discardCount[p] = floor(Random() * MAX_DECK);
        G.playedCardCount = 0;
        
        handPos = floor(Random() * handSize);
        
        testVal = checkSmithy(p,&G,handPos,handSize,deckSize);
        if(testVal == -1) {
            testsOk = 0;
            failCounter++;
        }
    }
    if(testsOk)
        printf("ALL TESTS OK\n");
    else
        printf("%d out of 20000 tests failed\n",failCounter);
    
    return 0;
}
