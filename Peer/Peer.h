#include "../managers/GameManager.h"
#include "../managers/NetworkManager.h"
#include "../managers/packet.h"
#include "../managers/ProtocolManager.h"
#define MAX_BUFFER 1024
class Peer {
private:
    char buf[MAX_BUFFER];
    short bufIdx;
    bool state;
    GameManager* GM;
    NetworkManager* NM;
    ProtocolManager* PM;
    
    void print(char* msg);
    void input();
    bool processBuffer();
public:
    Peer();
    ~Peer();
    void run();
};