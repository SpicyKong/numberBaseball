#include "NetworkManager.h"
#include <cstring>
#include <string>
#include <iostream>

NetworkManager::NetworkManager(int port)
{
    state = 1;
    port = port;
    FD_ZERO(&sockList);
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw "WSAStartup error";
    listeningSokcet = socket(PF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN servAdr;
    memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAdr.sin_port=htons(port);
    if(bind(listeningSokcet, (SOCKADDR*) &servAdr, sizeof(servAdr))==SOCKET_ERROR)
        throw "While binding a listening socket, error occured";
    if(listen(listeningSokcet, 10)==SOCKET_ERROR)
		throw "While starting a listening socket, error occured";
    FD_SET(listeningSokcet, &sockList);
}

NetworkManager::~NetworkManager()
{

    state = 0;
    for (int i=0; i<sockList.fd_count; i++) 
    {
        if (FD_ISSET(sockList.fd_array[i], &sockList))
            closesocket(sockList.fd_array[i]);
    }
    perror("asdf");
}

void NetworkManager::setMediator(IMediator* mediator)
{
    this->mediator = mediator;
}

void NetworkManager::changed()
{
    // 구현하다보니 안 씀, 추후 수정해야함
}

int NetworkManager::createSocket(const char* ip, const char* port)
{
    SOCKET tmpSock = socket(PF_INET, SOCK_STREAM, 0);
    if (tmpSock == INVALID_SOCKET)
        return 0;
    SOCKADDR_IN peerAdr;
    memset(&peerAdr, 0, sizeof(peerAdr));
    peerAdr.sin_family = AF_INET;
    peerAdr.sin_addr.s_addr = inet_addr(ip);
    peerAdr.sin_port = htons(atoi(port));

    if (connect(tmpSock, (SOCKADDR*)&peerAdr, sizeof(peerAdr)) == SOCKET_ERROR)
        return 0;
    FD_SET(tmpSock, &sockList);
    return tmpSock;
}

int NetworkManager::closeSocket(SOCKET sockId)
{
    FD_CLR(sockId, &sockList);
    return closesocket(sockId);
}
int NetworkManager::shutdownSocket(SOCKET sockId)
{
    FD_CLR(sockId, &sockList);
    return shutdown(sockId, SD_BOTH);
}

int NetworkManager::writeData(SOCKET sockId, const char* buf, int len)
{
    return send(sockId, buf, len, 0);
}

int NetworkManager::recvData(SOCKET sockId, char* buf, int len)
{

    return recv(sockId, buf, len, 0);
}

void NetworkManager::startListen()
{
    TIMEVAL timeout;
    int cnt=0;
    timeout.tv_sec =  1;
    timeout.tv_usec=1000;
    SOCKADDR_IN adrNewSocket;
    SOCKET newSocket;
    int adrSize;
    while (state)
    {
        
        updateList = sockList;
        cnt = select(0, &updateList, 0, 0, &timeout);
        if (cnt > 0)
        {
            //std::cout << sockList.fd_count << "\n";
            for (int i=0; i<sockList.fd_count; i++)
            {
                if (FD_ISSET(sockList.fd_array[i], &updateList) == 0)
                    continue;
                if (sockList.fd_array[i] == listeningSokcet)
                {
                    adrSize = sizeof(adrNewSocket);
                    newSocket = accept(listeningSokcet, (SOCKADDR*)&adrNewSocket, &adrSize);
                    FD_SET(newSocket, &sockList);
                }
                else
                {
                    
                    mediator->notify("SOCK_MESSAGE", sockList.fd_array[i]);
                }
            }

        }
            //changed();
        
    }
    std::cout << "closed\n";
}

/*
    00: 안녕 난 peer1인데 넌 누구니?
    01: 안녕 peer1반가워 난 peer2야
    02: 저기요? 살아있나요?

    03: 나랑 게임 셋업할래?
    04: 나는 준비가 다 되었어
    05: 게임시작하자
    06: 현재턴, 나의 guess 는 xxx야
    07: 그래 너의 xxx는 1s, 1b이야
    08: 우리 게임 종료하자(사유)

    09: 서버야 나 왔어
    10: 서버야 나 갈게
    11: 서버야 유저 목록을 알려줘
*/