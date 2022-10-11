#include "CurrentModule.h"
#include <Arduino.h>
#include <math.h>

const double CurrentModule::MIN_AMPS = 392.29;

CurrentModule::CurrentModule()
{
    setup();
}

void CurrentModule::setup()
{
    pinMode(A0, INPUT);
}

double CurrentModule::getVpp()
{
    double result;

    int readValue;       // value read from the sensor
    int maxValue = 0;    // store max value here
    int minValue = 1024; // store min value here

    uint32_t start_time = millis();
    while ((millis() - start_time) < 1000) // 1초동안 값을 모아서 AC 전류의 최고점, 최저점을 찾아 평균치를 구함
    {
        readValue = analogRead(PORT);
        if (readValue > maxValue)
        {
            maxValue = readValue;
        }
        if (readValue < minValue)
        {
            minValue = readValue;
        }
    }

    // Subtract min from max
    result = ((maxValue - minValue) * 5.0) / 1024.0; // 5V 분해능, 아날로그핀의 분해능 1024

    return result;
}

// 1초 동안의 평균 전류를 구하는 함수.
double CurrentModule::measure()
{
    double voltage = getVpp();
    double vrms = (voltage / 2.0) * 0.707;     // RMS값 70.7%
    double ampsRms = (vrms * 1000) / mVperAmp; // mA 단위 맞춰줌
    double result = ampsRms * 1000 - MIN_AMPS;
    if (result < 0)
    {
        result = 0;
    }
    return result;
}
