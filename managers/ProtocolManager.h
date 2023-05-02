#include <string>
class ProtocolManager {
private:

public:
    ProtocolManager();
    std::string makeMsgOnline();
    std::string makeMsgPing();
    std::string makeMsgOff();

    std::string makeMsgStart();
    std::string makeMsgClose(std::string );
    std::string makeMsgGuess(std::string guess);
    std::string makeMsgAnswer(std::string res);




};
/*

*/