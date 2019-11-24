CFLAGS= -Wall -fpic -coverage -lm -std=c99
COVERAGE= -Wall -fpic -ftest-coverage -fprofile-arcs -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c compare.h dominion.h dominion.c rngs.o
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(COVERAGE)

unittest2: unittest2.c compare.h dominion.h dominion.c rngs.o
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(COVERAGE)

unittest3: unittest3.c compare.h dominion.h dominion.c rngs.o
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(COVERAGE)

unittest4: unittest4.c compare.h dominion.h dominion.c rngs.o
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(COVERAGE)

unittest5: unittest5.c compare.h dominion.h dominion.c rngs.o
	gcc -o unittest5 unittest5.c dominion.c rngs.c $(COVERAGE)

unittestresults:
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(COVERAGE)
	./unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	rm dominion.gcda
	rm dominion.gcno
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(COVERAGE)
	./unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	rm dominion.gcda
	rm dominion.gcno
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(COVERAGE)
	./unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	rm dominion.gcda
	rm dominion.gcno
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(COVERAGE)
	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	rm dominion.gcda
	rm dominion.gcno
	gcc -o unittest5 unittest5.c dominion.c rngs.c $(COVERAGE)
	./unittest5 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	rm dominion.gcda
	rm dominion.gcno

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
