#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H

#include "IComponent.h"
#include "IMediator.h"
#include <WinSock2.h>

class NetworkManager : public IComponent {
private:
    IMediator* mediator;
    SOCKET listeningSokcet;
    fd_set sockList, updateList;
    int port;
    bool state;
    WSADATA wsaData;
public:
    NetworkManager(int port);
    ~NetworkManager();
    void setMediator(IMediator* mediator);
    void changed();
    int createSocket(const char* ip, const char* port);
    int closeSocket(SOCKET sockID);
    int shutdownSocket(SOCKET sockId);
    int writeData(SOCKET sockID, const char* buf, int len);
    int recvData(SOCKET sockID, char* buf, int len);
    void startListen();

};

#endif
/*
    스레드를 사용해서 리스닝 감지 
*/