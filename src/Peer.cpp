#include "Peer.h"
#include <cstring>
#include <thread>
#include <stdlib.h>
#include <string>
Peer::Peer()
{
    gm = new GameManager();
    //nm = new NetworkManager();
    cli = new Cli();
    cli->setMediator(this);
    state = 1;
}

Peer::~Peer()
{
    state = 0;
    delete gm, nm, cli;

}

void Peer::notify(std::string event)
{
    if (event == "KEY_PRESS") 
    {
        cli->consolePrint(std::string("key is pressed"));
    }
    else if (event == "STOP") 
    {
        cli->consolePrint(std::string("stopped"));
        state = 0;
    }
    else if (event == "TEST")
    {
        gm->createGame(1);
        gm->setAnswer(2, 123);
        gm->setAnswer(1, 124);
        //char* buf = "test";
        gm->submitGuess(1, 999);
        //cli->consolePrint(buf);
        gm->submitGuess(2, 999);
        //cli->consolePrint(buf);
        gm->submitGuess(1, 124);
        //cli->consolePrint(buf);
        cli->consolePrint(std::string("Done"));
    }
}

void Peer::run()
{
    std::thread consoleInterface(Cli::run, cli);
    while (state) {
        _sleep(1000);
        cli->consolePrint(std::string("something\n"));
    }
    consoleInterface.join();
}


int main() {
    Peer test = Peer();
    
    test.run();
}