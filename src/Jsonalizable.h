#ifndef JSONALIZABLE_H
#define JSONALIZABLE_H
#include <WString.h>
class Jsonalizable
{
public:
    virtual void json(char *buffer, int bufferSize) = 0;
};
#endif