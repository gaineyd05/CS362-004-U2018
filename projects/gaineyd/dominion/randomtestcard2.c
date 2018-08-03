#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

// checkFeast is identical to that written in Assignment 3 (cardtest1.c)
int checkFeast(int player, struct gameState *post, int choice, int currSupply) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    feastCard(post, choice);
    
    // TEST
    // printf("Reached this\n");
    
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

// TESTS FEAST CARD
int main(int argc, const char * argv[]) {
    int n, i, p, x, handPos, handSize, deckSize, discardSize, choice, currSupply;
    int testsOk, testVal;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    printf ("Testing smithyCard.\n");
    
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    testsOk = 1;
    // Much of setup of randomized gameState is based on provided example.
    for(n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // Set player, hand size, deck size, discard size, and supply count.
        p = floor(Random() * 2);
        G.whoseTurn = p;
        handSize = G.handCount[p] = floor(Random() * MAX_HAND);
        deckSize = G.deckCount[p] = floor(Random() * MAX_DECK);
        discardSize = G.discardCount[p] = floor(Random() * MAX_DECK);
        handPos = floor(Random() * handSize);
        x = floor(Random() * 10);
        choice = k[x];
        currSupply = G.supplyCount[k[x]] = floor(Random() * 10);
        floor(Random() * 3);
        
        testVal = checkFeast(p,&G,choice,currSupply);
        if(testVal == -1)
            testsOk = 0;
    }
    if(testsOk)
        printf("ALL TESTS OK\n");
    
    return 0;
}
