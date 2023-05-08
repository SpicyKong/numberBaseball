#ifndef _IMEDIATOR_H
#define _IMEDIATOR_H
#define interface class
#include <string>
class IComponent;

interface IMediator {
public:
    virtual void notify(std::string event, int id) = 0;
};

#endif