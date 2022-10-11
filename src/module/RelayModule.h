#ifndef RELAY_MODULE_H
#define RELAY_MODULE_H
#include <Arduino.h>
class RelayModule
{
private:
    const int PORT = D12;
    void setup();
    bool connected = true;

public:
    RelayModule();
    void connectElect();
    void breakElect();
    bool isConnected();
};
#endif