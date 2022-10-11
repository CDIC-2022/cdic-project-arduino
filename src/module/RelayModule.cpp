#include "RelayModule.h"
RelayModule::RelayModule()
{
    setup();
}

void RelayModule::setup()
{
    pinMode(PORT, OUTPUT);
}

void RelayModule::connectElect()
{
    connected = true;
    digitalWrite(PORT, HIGH);
}

void RelayModule::breakElect()
{
    connected = false;
    digitalWrite(PORT, LOW);
}

bool RelayModule::isConnected()
{
    return this->connected;
}
