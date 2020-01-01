#include <Arduino.h>
#include "main.h"
#include <WiFi.h>
#include <WiFiAP.h>

const char ssid[] = "OSCNet";
const char password[] = "oscnet1324";

static const char buildInfoLogString[] = "Build data: %s, %s %s";
char logBuffer[256];

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    sprintf(logBuffer, buildInfoLogString, PIO_GIT_REV, __DATE__, __TIME__);
    Serial.println(logBuffer);
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    sprintf(logBuffer, "OSCNet server IP: %s", myIP.toString().c_str());
    Serial.println(logBuffer);

    server.begin();
    Serial.println("Server started");
}

void loop()
{
}