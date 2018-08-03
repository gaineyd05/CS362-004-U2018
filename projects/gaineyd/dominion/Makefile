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

testGainCard: unittest1.c dominion.o rngs.o
	gcc -o testGainCard -g  unittest1.c dominion.o rngs.o $(CFLAGS)

testGameOver: unittest3.c dominion.o rngs.o
	gcc -o testGameOver -g  unittest3.c dominion.o rngs.o $(CFLAGS)

testDiscardCard: unittest2.c dominion.o rngs.o
	gcc -o testDiscardCard -g  unittest2.c dominion.o rngs.o $(CFLAGS)

testFullCount: unittest4.c dominion.o rngs.o
	gcc -o testFullCount -g  unittest4.c dominion.o rngs.o $(CFLAGS)

testCards: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -o testGainCard -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o testDiscardCard -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o testGameOver -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o testFullCount -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	testGainCard >> unittestresults.out
	gcov dominion.c -f -b >> unittestresults.out
	testDiscardCard >> unittestresults.out
	gcov dominion.c -f -b >> unittestresults.out
	testGameOver >> unittestresults.out
	gcov dominion.c -f -b >> unittestresults.out
	testFullCount >> unittestresults.out
	gcov dominion.c -f -b >> unittestresults.out
	cardtest1 >> unittestresults.out
	gcov dominion.c -f -b >> unittestresults.out

randomTest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtest1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	randomtest1 >> randomtestcard1.out
	gcov dominion.c -f -b >> randomtestcard1.out

randomTest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtest2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomTestAdv: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadv -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testGainCard testDiscardCard testGameOver cardtest1 testFullCount cardtest2 cardtest3 cardtest4 randomtest1 randomtest2 randomtestadv
