#include "ArduinoCondition.h"
double ArduinoCondition::getCurrent()
{
    return this->current;
}

bool ArduinoCondition::isConnected()
{
    return this->connected;
}

void ArduinoCondition::json(char *buffer, int bufferSize)
{
    snprintf(buffer, bufferSize, "{\"isConnected\": \"%d\", \"current\": \"%f\", \"MAC\": \"%s\"}", connected, current, macAddr.c_str());
}