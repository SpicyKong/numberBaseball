#ifndef _CLI_H
#define _CLI_H

#include "IComponent.h"
#include "IMediator.h"
#include <deque>
#include <string>

class Cli : public IComponent {
private:
    std::deque<char> bufLeft, bufRight;
    bool state;
    IMediator* mediator;
    void clearBuf();
    void consoleSyncCursor();
    void consoleInput();
    void consoleHideBuf();
    void consolePrintBuf();
public:
    Cli();
    ~Cli();
    void setState(bool s);
    void setMediator(IMediator* mediator);
    void changed();
    void run();
    void consolePrint(std::string msg);
};
#endif