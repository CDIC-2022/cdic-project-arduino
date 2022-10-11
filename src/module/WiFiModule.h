#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "library/Logger/Logger.h"
class WiFiModule
{
public:
    void connectAP(const char *ssid, const char *pwd);
    String getMacAddr();
};
#endif