#ifndef SWITCH_MODULE_H
#define SWITCH_MODULE_H
#include <Arduino.h>
class SwitchModule
{
private:
    const int PORT = D8;

public:
    SwitchModule();
    void setup();
    bool isOn();
};
#endif