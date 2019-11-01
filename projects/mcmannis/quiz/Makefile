all: testme
	./testme

testme: testme.c
	gcc -o testme testme.c -Wall -fpic -ftest-coverage -fprofile-arcs -lm -std=c99
