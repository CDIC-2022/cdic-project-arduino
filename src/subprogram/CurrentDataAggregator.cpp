#include "CurrentDataAggregator.h"

void CurrentDataAggregator::collect(double currentData)
{
    buffer[currentIdx] = currentData;
    Log.noticeln("%d ~ %d초 동안 측정한 전류값: %D mA", currentIdx, currentIdx + 1, currentData);
    currentIdx++;
    if (currentIdx == BUFFER_MAX_SIZE)
    {
        currentIdx = 0;
        isBufferFull = true;
    }
}

double CurrentDataAggregator::calculateAverageCurrent()
{
    double sum = 0;
    int bufferLen = 0;
    if (isBufferFull)
    {
        bufferLen = BUFFER_MAX_SIZE;
    }
    else
    {
        bufferLen = currentIdx;
    }
    for (int i = 0; i < bufferLen; i++)
    {
        sum += buffer[i];
    }
    double averageCurrent = sum / bufferLen;
    Log.noticeln("1분간 평균 전류값: %D mA", averageCurrent);
    return averageCurrent;
}

void CurrentDataAggregator::reset()
{
    currentIdx = 0;
    isBufferFull = false;
}