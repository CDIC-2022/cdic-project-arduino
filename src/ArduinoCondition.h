#ifndef ARDUINO_CONDITION_H
#define ARDUINO_CONDITION_H
#include "Jsonalizable.h"
#include <string>
#include <WString.h>
#include "library/Logger/Logger.h"
class ArduinoCondition : public Jsonalizable
{
private:
    double current;
    bool connected;
    String macAddr;

public:
    ArduinoCondition(double _current, bool _connected, String _macAddr) : current(_current), connected(_connected), macAddr(_macAddr) {}
    double getCurrent();
    bool isConnected();
    void json(char* buffer, int bufferSize);
};
#endif