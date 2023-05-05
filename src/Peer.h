#ifndef _PEER_H
#define _PEER_H

#include "IMediator.h"
#include "GameManager.h"
#include "NetworkManager.h"
#include "Cli.h"

class Peer : public IMediator {
private:
    GameManager* gm;
    NetworkManager* nm;
    Cli* cli;
    bool state;
public:
    Peer();
    ~Peer();
    void notify(char* event);
    void run();
};
#endif