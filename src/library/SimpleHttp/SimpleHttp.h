#ifndef SIMPLE_HTTP_H
#define SIMPLE_HTTP_H
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Jsonalizable.h>
#include <library/Logger/Logger.h>
#define HTTP_ERROR_MSG ""
class SimpleHttp
{
private:
    HTTPClient httpClient;
    WiFiClient wifiClient;

public:
    String requestByPost(const char *url, Jsonalizable &data);
};
#endif