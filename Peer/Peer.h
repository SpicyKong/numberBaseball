#include "../managers/GameManager.h"
#include "../managers/NetworkManager.h"
#include "../managers/packet.h"
#include "../managers/ProtocolManager.h"
#include <deque>

class Peer {
private:
    std::deque<char> bufLeft, bufRight;
    bool state;
    GameManager* GM;
    NetworkManager* NM;
    ProtocolManager* PM;
    

    void consolePrint(char* msg);
    void consolePrintBuf();
    void consoleHideBuf();
    void consoleInput();
    void consoleSyncCursor();
    void getWord(char* buf);
    void processBuffer();
    void clearBuf();
public:
    Peer();
    ~Peer();
    void run();
};