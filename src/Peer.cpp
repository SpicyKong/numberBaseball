#include "Peer.h"
#include <cstring>
#include <thread>
#include <stdlib.h>

Peer::Peer()
{
    //gm = new GameManager();
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

void Peer::notify(char* event)
{
    if (strcmp(event, "KEY_PRESS") == 0) 
    {
        cli->consolePrint("key is pressed");
    }
    if (strcmp(event, "STOP") == 0) 
    {
        cli->consolePrint("stopped");
        state = 0;
    }
}

void Peer::run()
{
    std::thread consoleInterface(Cli::run, cli);
    while (state) {
        _sleep(1000);
        cli->consolePrint("something\n");
    }
    consoleInterface.join();
}


int main() {
    Peer test = Peer();
    test.run();
}