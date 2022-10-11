#include "SimpleHttp.h"
String SimpleHttp::requestByPost(const char *url, Jsonalizable &data)
{
    // Log.noticeln("URL: %s", url);
    httpClient.begin(wifiClient, url);
    httpClient.addHeader("Content-Type", "application/json");
    int payloadSize = 512;
    char payload[payloadSize];
    data.json(payload, payloadSize);
    // Log.noticeln("서버에서 온 명령: %s", payload);
    int httpResponseCode = httpClient.POST(String(payload));

    if (httpResponseCode < 0 || httpResponseCode != HTTP_CODE_OK)
    {
        // Log.noticeln("Request error - %d", httpResponseCode);
        return HTTP_ERROR_MSG;
    }
    String response = httpClient.getString();
    httpClient.end();

    return response;
}