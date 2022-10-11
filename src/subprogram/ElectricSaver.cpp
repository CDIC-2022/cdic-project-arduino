#include "ElectricSaver.h"

void ElectricSaver::run(double averageCurrent)
{
    if (averageCurrent <= MARGIN_AMPS)
    {
        Log.noticeln("전류가 자동으로 차단되었습니다.");
        relayModule.breakElect();
    }
}