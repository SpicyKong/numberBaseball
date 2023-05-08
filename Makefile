#g++ = g++
SRC = ./src
all: Peer RegiServer
Peer : Peer.o  Cli.o GameManager.o NetworkManager.o Game.o $(SRC)/tools.cpp
	g++ -o Peer Peer.o Cli.o GameManager.o NetworkManager.o Game.o -lws2_32

RegiServer : RegiServer.o NetworkManager.o
	g++ -o RegiServer RegiServer.o NetworkManager.o -lws2_32

RegiServer.o : $(SRC)/RegiServer.h $(SRC)/RegiServer.cpp
	g++ -c -o RegiServer.o $(SRC)/RegiServer.cpp

Peer.o : $(SRC)/Peer.h $(SRC)/Peer.cpp
	g++ -c -o Peer.o $(SRC)/Peer.cpp

NetworkManager.o : $(SRC)/NetworkManager.cpp $(SRC)/NetworkManager.h
	g++ -c $(SRC)/NetworkManager.cpp -lws2_32

GameManager.o : $(SRC)/GameManager.cpp $(SRC)/GameManager.h
	g++ -c $(SRC)/GameManager.cpp

Game.o : $(SRC)/Game.cpp $(SRC)/game.h
	g++ -c $(SRC)/Game.cpp

Cli.o : $(SRC)/Cli.cpp $(SRC)/Cli.h
	g++ -c $(SRC)/Cli.cpp

clean : 
	rm *.o
#gcc test.c -lws2_32