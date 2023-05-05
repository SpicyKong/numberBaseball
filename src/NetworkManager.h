#ifndef _NETWORKMANAGER_H
#define _NETWORKMANAGER_H

#include "IComponent.h"

class NetworkManager : public IComponent {
private:
public:
    void setMediator(IMediator* mediator);
    void changed();
};

#endif