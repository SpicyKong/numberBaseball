#include "Cli.h"

#include <conio.h>
#include <thread>
#include <iostream>

void Cli::clearBuf()
{
    bufLeft.clear();
    bufRight.clear();
}

void Cli::consoleSyncCursor()
{
    for (int i=0; i<bufRight.size(); i++)
        std::cout << (char)8;
}

void Cli::consoleInput()
{
    char key;
    while (state) 
    {
        key = _getch();
        switch (key)
        {
        case 3: // ctrl c
            state = 0;
            break;
        case 13: // Enter key
            changed();
            clearBuf();
            break;
        case 8: // back space
            if (bufLeft.size() == 0)
                continue;
            consoleHideBuf();
            bufLeft.pop_back();
            consolePrintBuf();
            break;
        case 75: // left key
            if (bufLeft.size() == 0)
                continue;
            bufRight.push_front(bufLeft.back());
            bufLeft.pop_back();
            consoleHideBuf();
            consolePrintBuf();
            break;
        case 72: // up key
            mediator->notify("STOP", 0);
            state = 0;
            break;
        case 77: // right key
            if (bufRight.size() == 0)
                continue;
            bufLeft.push_back(bufRight.front());
            bufRight.pop_front();
            std::cout << bufLeft.back();
            break;
        case 80: // down key
            mediator->notify("TEST", 0);
            break;
        case 83: //delete
            if (bufRight.size() == 0)
                continue;
            consoleHideBuf();
            bufRight.pop_front();
            consolePrintBuf();
            break;
        default:
            if (key < 32 || key > 127)
                continue;
            bufLeft.push_back(key);
            consoleHideBuf();
            consolePrintBuf();
            break;
        }
    }
}

void Cli::consoleHideBuf()
{
    printf("\r");
    for (int i=0; i<bufLeft.size() + bufRight.size(); i++)
        std::cout << " ";
    std::cout << "\r";
}

void Cli::consolePrintBuf()
{
    for (auto it = bufLeft.begin(); it != bufLeft.end(); it++)
        std::cout << *it;
    for (auto it = bufRight.begin(); it != bufRight.end(); it++)
        std::cout << *it;
    consoleSyncCursor();
}

void Cli::setState(bool s) 
{
    state = s;
}

void Cli::setMediator(IMediator* mediator)
{
    this->mediator = mediator;
}

void Cli::changed()
{
    if (mediator == nullptr)
        return;
    //std::string eventName = "KEY_PRESS";
    mediator->notify("KEY_PRESS", 0);
}

void Cli::run()
{
    
    std::thread inputThread(consoleInput, this);
    inputThread.join();
}

void Cli::consolePrint(std::string msg)
{
    consoleHideBuf();
    std::cout << msg << "\n";
    consolePrintBuf();
}

Cli::Cli()
{
    state = 1;

}

Cli::~Cli()
{
    state = 0;
}

std::string Cli::getLine()
{
    std::string ret="";
    for (auto i=bufLeft.begin(); i!=bufLeft.end(); i++)
    {
        ret+=*i;
    }

    for (auto i=bufRight.begin(); i!=bufRight.end(); i++)
    {
        ret+=*i;
    }
    clearBuf();
    return ret;
}