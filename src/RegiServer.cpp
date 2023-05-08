#include "RegiServer.h"
#include <iostream>
#include <thread>
#include "tools.cpp"

RegiServer::RegiServer(int port)
{
    nm = new NetworkManager(port);
    nm->setMediator(this);
    connections=0;
    idBitSet = 0;
}

RegiServer::~RegiServer()
{
    delete nm;
}

void RegiServer::notify(std::string event, int id)
{
    if (event == "SOCK_MESSAGE")
    {
        HEADER packetHeader{-1, -1, -1}, myHeader;
        USERINFO user{-1, 0, 0};
        if (nm->recvData(id, (char*)&packetHeader, sizeof(packetHeader)) <= 0)
        {
            nm->shutdownSocket(id);// 강제 삭제 찾아보기
            // 여기서 소켓 아이디로 정보 삭제
            deletePeer(sock2peer[id]);
            return;
        }
        switch (packetHeader.hId)
        {
        case 10: // 유저 로그인 => 생성하고 아이디 반환
            if (userVerify(packetHeader.peerId, id) == 0)
            {
                //m.lock();
                nm->recvData(id, (char*)&user, packetHeader.size);
                int pid = createPeer(id, user.ip, user.port);
                //std::cout << ip2str(user.ip) << "<==ip\n";
                myHeader = {0, 11, pid};
                nm->writeData(id, (char*)&myHeader, sizeof(myHeader));
                //m.unlock();
            }
            break;
        case 12: // 유저 로그아웃 => 아이디 삭제하고 소켓 삭제
            if (userVerify(packetHeader.peerId, id))
            {
                //m.lock();
                deletePeer(packetHeader.peerId);
                //m.unlock();
            }
            break;
        case 13: // 유저 목록 요청 => 유저 목록 뽑아서 헤더 먼저 보내고 바디 보냄
            //m.lock();
            myHeader = {((int)sizeof(USERINFO))*connections, 14, -1}; // 스레드 보호 필요
            nm->writeData(id, (char*)&myHeader, sizeof(myHeader));
            for (auto i = peer2host.begin(); i!=peer2host.end(); i++) 
            {
                nm->writeData(id, (char*)&(i->second), sizeof(USERINFO));
            }
            //m.unlock();
            break;
        default:
            break;
        }

    }
}
/*
    10: 서버야 나 왔어
    11: 서버야 나 갈게
    12: 서버야 유저 목록을 알려줘
    13: 유저목록 여기 (헤더에서 전체 사이즈 알려줌)
*/
void RegiServer::run()
{
    std::thread networkListening(NetworkManager::startListen, nm);
    networkListening.join();
    //nm->startListen();
}


int RegiServer::getFreeId()
{
    int id=0;
    long long tmp = idBitSet;
    while (tmp)
    {
        if ((tmp & 1)==0)
            return id;
        tmp >>= 1;
        ++id;
    }
    return id;
}

void RegiServer::setId(int id)
{
    if (id >= 64)
        return;
    idBitSet |= (1<<id);
}

void RegiServer::deleteId(int id)
{
    if (id >= 64)
        return;
    idBitSet &= ~(1<<id);
}

int RegiServer::createPeer(int sockId, int ip, int port)
{
    if (connections >= 64)
    {
        return 0;
    }
    int peerId = getFreeId();
    setId(peerId);
    USERINFO user {peerId, port, ip};
    peer2host[peerId] = user;
    peer2sock[peerId] = sockId;
    sock2peer[sockId] = peerId;
    ++connections;
    return peerId;
}

void RegiServer::deletePeer(int pid)
{
    nm->closeSocket(peer2sock[pid]);
    sock2peer.erase(peer2sock[pid]);
    peer2sock.erase(pid);
    peer2host.erase(pid);
    deleteId(pid);
    --connections;
}

bool RegiServer::userVerify(int pid, int sockId)
{
    // 등록된 사용자면 1 아니면 0 반환
        if (peer2host.find(pid) == peer2host.end())
            return 0;
        if (sock2peer.find(sockId) == sock2peer.end())
            return 0;
        if (sock2peer[sockId] == pid)
            return 1;
        return 0;
}

std::mutex RegiServer::m;

int main() 
{
    int port=5000;
    std::cout << "Input port number: ";
    std::cin >> port;
    RegiServer server = RegiServer(port);
    server.run();
}