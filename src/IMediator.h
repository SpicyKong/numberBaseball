#ifndef _IMEDIATOR_H
#define _IMEDIATOR_H
#define interface class

interface IMediator {
public:
    virtual void notify(char* event) = 0;
};

#endif