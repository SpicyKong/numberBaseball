#ifndef _REGISERVER_H
#define _REGISERVER_H

#include "IMediator.h"
#include "NetworkManager.h"
#include <algorithm>
#include "Packet.h"
#include <mutex>
#include <map>

class RegiServer : public IMediator {
private:
    NetworkManager* nm;
    std::map<int, int> peer2sock;
    std::map<int, int> sock2peer;
    std::map<int, USERINFO> peer2host;
    int connections;
    long long idBitSet;

    int getFreeId();
    void setId(int id);
    void deleteId(int id);
    int createPeer(int sockId, int ip, int port);
    void deletePeer(int pid);
    bool userVerify(int pid, int sockId);
    static std::mutex m;
public:
    RegiServer(int port);
    ~RegiServer();
    void notify(std::string event, int id);
    void run();

};
#endif