#ifndef LOGGER_H
#define LOGGER_H
#include <ArduinoLog.h>
class Logger
{
private:
    Logger();
    struct constructor
    {
        constructor()
        {
            setup();
        }
    };

    static constructor cons;

public:
    static void setup();
    static void printPrefix(Print *_logOutput, int logLevel);
    static void printSuffix(Print *_logOutput, int logLevel);
    static void printTimestamp(Print *_logOutput);
    static void printLogLevel(Print *_logOutput, int logLevel);
};
#endif