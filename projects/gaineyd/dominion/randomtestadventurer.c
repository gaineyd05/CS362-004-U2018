#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

// Due to randomness of generated decks, checkAdventurer only determines whether function returned with a value that is possible.
int checkAdventurer(int player, struct gameState *post, int deckSize, int discardSize) {
    // printf("hi\n");
    adventurerCard(post);
    // printf("bye\n");
    updateCoins(player,post,0);
    
    // Due to random
    if(post->coins <= 6 && post->coins >= 0) {
        printf("TEST FAILED          Player: %d, Coins: %d, Deck Size: %d, Discard Size: %d\n",player, post->coins, deckSize, discardSize);
        return -1;
    } else {
        printf("OK                   Player: %d, Coins: %d, Deck Size: %d, Discard Size: %d\n",player, post->coins, deckSize, discardSize);
        return 0;
    }
    
}

// TESTS ADVENTURER CARD
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
        
        // Additional setup nearly identical to that for smithy random tests due to similar dependencies
        p = floor(Random() * 2);
        G.whoseTurn = p;
        handSize = G.handCount[p] = floor(Random() * MAX_HAND);
        memset(G.hand[p], 0, sizeof(int) * handSize);
        deckSize = G.deckCount[p] = floor(Random() * MAX_DECK);
        discardSize = G.discardCount[p] = floor(Random() * MAX_DECK);
        G.playedCardCount = 0;
        
        handPos = floor(Random() * handSize);
        
        testVal = checkAdventurer(p,&G,deckSize,discardSize);
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
