#ifndef CURRENT_MODULE_H
#define CURRENT_MODULE_H
#include <Arduino.h>
#include "library/Logger/Logger.h"
class CurrentModule
{
private:
    const int PORT = A0;
    const int mVperAmp = 66;
    const static double MIN_AMPS;
    void setup();
    double getVpp();
    double current;

public:
    CurrentModule();
    double measure();
};
#endif