#ifndef _ICOMPONENT_H
#define _ICOMPONENT_H

#define interface class
class IMediator;

interface IComponent {
public:
    virtual void setMediator(IMediator* mediator) = 0;
    virtual void changed() = 0;
};

#endif