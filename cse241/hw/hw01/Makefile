all: main

main: main.o peg_solitaire.o
	g++ main.o peg_solitaire.o -o main

main.o: main.cpp
	g++ --std=c++11 main.cpp -c

peg_solitaire.o: peg_solitaire.cpp
	g++ --std=c++11 peg_solitaire.cpp -c

clean:
	rm -f *.o main