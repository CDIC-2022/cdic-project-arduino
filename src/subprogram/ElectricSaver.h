#ifndef ELECTRIC_SAVER_H
#define ELECTRIC_SAVER_H
#include "../module/RelayModule.h"
#include "library/Logger/Logger.h"
class ElectricSaver
{
private:
    RelayModule relayModule;
    // const static int MIN_AMPS = 4440.59;
    // const static int MIN_AMPS = 52.31;

    // const static int MARGIN_AMPS = 30;
    const static int MARGIN_AMPS = 500;

public:
    ElectricSaver(RelayModule &_relayModule) : relayModule(_relayModule) {}
    void run(double averageCurrent);
};
#endif