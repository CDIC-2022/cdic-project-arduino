#include "SwitchModule.h"

SwitchModule::SwitchModule()
{
    setup();
}

void SwitchModule::setup()
{
    pinMode(PORT, INPUT_PULLUP);
}

bool SwitchModule::isOn()
{
    if (digitalRead(PORT) == LOW)
    {
        return true;
    }
    else
    {
        return false;
    }
}