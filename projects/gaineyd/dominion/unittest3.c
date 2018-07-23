#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1


int checkIsGameOver(struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    int r;
    r = isGameOver(post);
    
    int i;
    int counter = 0;
    int isOver = 0;
    for(i = 0; i < 25; i++) {
        if(pre.supplyCount[i] == 0)
            counter++;
    }
    if(counter >= 3 || pre.supplyCount[province] == 0)
        isOver = 1;
    
    if(r != isOver) {
        printf("TEST FAILED\n");
        return -1;
    } else {
        // printf("OK\n");
        return 0;
    }
}

// Tests whether isGameOver function adds the requested card correctly.
int main() {
    // Setup and loop structure is based on provided examples
    int n, x, testVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    printf ("Testing isGameOver.\n");
    printf ("FIXED TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    int testsOk = 1;
    // Check for all supplies initialized with positive or zero values or with mixed values
    for(n = 0; n < 25; n++) {
        for(x = 0; x < 25; x++) {
            initializeGame(2, k, 1, &G);
            G.supplyCount[x] = 10;
            G.supplyCount[n] = 0;
            testVal = checkIsGameOver(&G);
            if(testVal == -1)
                testsOk = 0;
        }
    }
    if(testsOk)
        printf("ALL TESTS OK\n");
    
    return 0;
}
