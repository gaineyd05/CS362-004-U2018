CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testAdventurer: cardtest4.c randomtestadventurer.c dominion.o rngs.o
	gcc -o advunittest cardtest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o advrandtest randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

testSmithy: cardtest1.c randomtestcard1.c dominion.o rngs.o
	gcc -o smtunittest cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o smtrandtest randomtestcard1.c dominion.o rngs.o $(CFLAGS)

testFeast: cardtest2.c randomtestcard2.c dominion.o rngs.o
	gcc -o feaunittest cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o fearandtest randomtestcard2.c dominion.o rngs.o $(CFLAGS)

testCouncilRoom: cardtest3.c dominion.o rngs.o
	gcc -o corunittest cardtest3.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
