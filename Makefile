#g++ = g++
SRC = ./src

peer : peer.o  Cli.o GameManager.o NetworkManager.o Game.o
	g++ -o peer peer.o Cli.o GameManager.o NetworkManager.o Game.o

peer.o : $(SRC)/peer.h $(SRC)/peer.cpp
	g++ -c -o peer.o $(SRC)/peer.cpp

NetworkManager.o : $(SRC)/NetworkManager.cpp $(SRC)/NetworkManager.h
	g++ -c $(SRC)/NetworkManager.cpp

GameManager.o : $(SRC)/GameManager.cpp $(SRC)/GameManager.h
	g++ -c $(SRC)/GameManager.cpp

Game.o : $(SRC)/Game.cpp $(SRC)/game.h
	g++ -c $(SRC)/Game.cpp

Cli.o : $(SRC)/Cli.cpp $(SRC)/Cli.h
	g++ -c $(SRC)/Cli.cpp

clean : 
	rm *.o