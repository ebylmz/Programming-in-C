all: test

test: test.o peg_solitaire.o
	g++ test.o peg_solitaire.o -o test

test.o: test.c
	g++ --std=c++11 test.c -c

peg_solitaire.o
	g++ --std=c++11 peg_solitaire.c

clean:
	rm -f *.o test