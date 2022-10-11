#include "WiFiModule.h"

void WiFiModule::connectAP(const char *ssid, const char *pwd)
{
    Serial.println("");
    Log.noticeln("와이파이 [ %s ]에 연결을 시도합니다.", ssid);
    WiFi.begin(ssid, pwd);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Log.noticeln("와이파이 [ %s ]에 연결되었습니다.", ssid);
    Log.noticeln("IP 주소: %p", WiFi.localIP());
    Log.noticeln("MAC 주소: %s", WiFi.macAddress().c_str());
}

String WiFiModule::getMacAddr()
{
    return WiFi.macAddress();
}
