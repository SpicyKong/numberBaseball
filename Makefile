#g++ = g++
SRC = ./managers

peer : peer.o
	g++ -o peer peer.o GameManager.o NetworkManager.o protocolManager.o

#regiServer : regiServer.o
#	g++ -o regiServer.o NetworkManager.o protocolManager.o

peer.o : ./peer/peer.cpp GameManager.o NetworkManager.o protocolManager.o
	g++ -c -o peer.o ./peer/peer.cpp GameManager.o NetworkManager.o protocolManager.o

#regiServer.o : ./regiServer/regiServer.cpp NetworkManager.o protocolManager.o
#	g++ -c -o regiServer.o ./regiServer/regiServer.cpp NetworkManager.o protocolManager.o

GameManager.o : $(SRC)/GameManager.cpp $(SRC)/GameManager.h
	g++ -c $(SRC)/GameManager.cpp

NetworkManager.o : $(SRC)/NetworkManager.cpp $(SRC)/NetworkManager.h
	g++ -c $(SRC)/NetworkManager.cpp

protocolManager.o : $(SRC)/protocolManager.cpp $(SRC)/protocolManager.h
	g++ -c $(SRC)/protocolManager.cpp


clean : 
	rm *.o