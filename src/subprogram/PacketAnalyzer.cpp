#include "PacketAnalyzer.h"
int PacketAnalyzer::run(String packetPayload)
{
    // Log.noticeln("Payload: %s", packetPayload.c_str());
    int command = packetPayload.c_str()[0] - '0';
    // Log.noticeln("Command: %d", command);
    switch (command)
    {
    case CMD_FROM_SERVER::CONNECT_CURRENT:
    case CMD_FROM_SERVER::BREAK_CURRENT:
    case CMD_FROM_SERVER::NO_ACTION:
        return command;
    default:
        return CMD_FROM_SERVER::UNDEFINED;
    }
    return CMD_FROM_SERVER::UNDEFINED;
}