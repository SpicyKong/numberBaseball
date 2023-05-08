#ifndef _PEER_H
#define _PEER_H

#include "IMediator.h"
#include "IComponent.h"
#include "GameManager.h"
#include "NetworkManager.h"
#include "Cli.h"
#include <string>
#include <map>

class Peer : public IMediator {
private:
    GameManager* gm;
    NetworkManager* nm;
    Cli* cli;
    std::map<int, int> peer2sock, sock2peer;
    int peerId, serverSock, port;
    bool state;
public:
    Peer(int myPort);
    ~Peer();
    void notify(std::string event, int id);
    void run(std::string serverIp, std::string serverPort);
};
#endif