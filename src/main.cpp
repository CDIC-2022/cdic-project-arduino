#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
#include <arduino-timer.h>
#include "library/Logger/Logger.h"
#include "secret/ServerSecret.h"
#include "secret/WiFiSecret.h"
#include "ArduinoCondition.h"
#include "constant/CommandInPacket.h"
#include "module/AllModule.h"
#include "library/SimpleHttp/SimpleHttp.h"
#include "subprogram/PacketAnalyzer.h"
#include "subprogram/CurrentDataAggregator.h"
#include "subprogram/ElectricSaver.h"
#include "constant/ServerUrl.h"
#include "subprogram/RestoreButtonObserver.h"
#define INTERVAL_CHECK_CONDITION 1000 * 1000
#define INTERVAL_INFORM_SERVER_OF_CONDITION 1000 * 1000 * 5
#define INTERVAL_CALCULATE_AVERAGE_CURRENT 1000 * 1000 * 60
#define INTERVAL_SAVE_ELECTRIC INTERVAL_CALCULATE_AVERAGE_CURRENT
#define INTERVAL_INFORM_SERVER_OF_AVERAGE_CURRENT INTERVAL_CALCULATE_AVERAGE_CURRENT

unsigned long previousMillis = 0;
const long interval = 1000 * 10;

WiFiModule wifiModule;
RelayModule relayModule;
CurrentModule currentModule;
SimpleHttp http;
PacketAnalyzer packetAnalyzer;
Timer<1, micros> timerForCheckingCondition;
Timer<1, micros> timerForInformingConditionOfServer;
Timer<1, micros> timerForCalculatingAverageCurrentAndInformServer;
Timer<1, micros> timerForSavingElectric;
double current = 0;
double averageCurrent = -1;
CurrentDataAggregator aggregator;
ElectricSaver saver(relayModule);
String macAddr;

void initSerial();
void initWiFi();
void initRelayModule();
void initTimer();
void send(const char *url, ArduinoCondition condition);
void setup()
{
  initSerial();
  initWiFi();
  initTimer();
  initRelayModule();
  macAddr = wifiModule.getMacAddr();
}

void initRelayModule()
{
  relayModule.connectElect();
}

void initSerial()
{
  Serial.begin(115200);
}

void initWiFi()
{
  wifiModule.connectAP(WIFI::SSID, WIFI::PWD);
}

void initTimer()
{
  timerForCheckingCondition.every(INTERVAL_CHECK_CONDITION, [](void *)
                                  {current = currentModule.measure();
                                  aggregator.collect(current);
                                 return true; });
  timerForInformingConditionOfServer.every(INTERVAL_INFORM_SERVER_OF_CONDITION, [](void *)
                                           {bool connected = relayModule.isConnected();
                                           ArduinoCondition condition(current,connected,macAddr);
                                           send(SERVER_URL::TELL_CONDITION, condition); 
                                           return true; });
  timerForCalculatingAverageCurrentAndInformServer.every(INTERVAL_CALCULATE_AVERAGE_CURRENT, [](void *)
                                                         {averageCurrent = aggregator.calculateAverageCurrent();
                                                          aggregator.reset(); 
                                                          bool connected = relayModule.isConnected();
                                                          ArduinoCondition condition(averageCurrent,connected,macAddr);
                                                          send(SERVER_URL::TELL_AVERAGE_CURRENT,condition);
                                                          return true; });
  timerForSavingElectric.every(INTERVAL_SAVE_ELECTRIC, [](void *)
                               {if(averageCurrent != -1)
                               {saver.run(averageCurrent);}
                               return true; });
}

void send(const char *url, ArduinoCondition condition)
{
  String packetPayload = http.requestByPost(url, condition);
  int cmd = packetAnalyzer.run(packetPayload);
  switch (cmd)
  {
  case CMD_FROM_SERVER::CONNECT_CURRENT:
    Log.noticeln("서버에서 온 명령: 전류 연결.");
    relayModule.connectElect();
    break;
  case CMD_FROM_SERVER::BREAK_CURRENT:
    Log.noticeln("서버에서 온 명령: 전류 차단.");
    relayModule.breakElect();
    break;
  case CMD_FROM_SERVER::NO_ACTION:
    // Log.noticeln("Command in packet: No action.");
    break;
  case CMD_FROM_SERVER::UNDEFINED:
    // Log.noticeln("Error: Command not found.");
    break;
  }
}

SwitchModule switchModule;
RestoreButtonObserver observer(switchModule, relayModule);

void loop()
{
  timerForCheckingCondition.tick();
  timerForInformingConditionOfServer.tick();
  timerForCalculatingAverageCurrentAndInformServer.tick();
  timerForSavingElectric.tick();
  observer.restoreIfButtonIsPressed();
}