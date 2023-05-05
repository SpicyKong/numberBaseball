#ifndef _IMEDIATOR_H
#define _IMEDIATOR_H
#define interface class
#include <string>

interface IMediator {
public:
    virtual void notify(std::string event) = 0;
};

#endif