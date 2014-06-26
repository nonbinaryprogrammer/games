all: game.o gofish.o assignment3.o poker.o
	g++ assignment3.o gofish.o game.o poker.o -o out

assignment3.o: assignment3.cpp
	g++ assignment3.cpp -c

game.o: game.cpp
	g++ game.cpp -c
	
gofish.o: gofish.cpp
	g++ gofish.cpp -c

poker.o: poker.cpp
	g++ poker.cpp -c
	
clean:
	rm -f *.out *.o out
