#ifndef _PEER_H
#define _PEER_H

#include "IMediator.h"
#include "GameManager.h"
#include "NetworkManager.h"
#include "Cli.h"
#include <string>

class Peer : public IMediator {
private:
    GameManager* gm;
    NetworkManager* nm;
    Cli* cli;
    bool state;
public:
    Peer();
    ~Peer();
    void notify(std::string event);
    void run();
};
#endif