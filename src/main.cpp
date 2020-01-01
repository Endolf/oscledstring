#include <Arduino.h>
#include "main.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

static const char buildInfoLogString[] = "Build data: %s, %s %s";

const char ssid[] = "OSCNet";
const char password[] = "oscnet1324";

char logBuffer[256];

WiFiUDP Udp;
OSCErrorCode error;

void setup()
{
    Serial.begin(115200);
    sprintf(logBuffer, buildInfoLogString, PIO_GIT_REV, __DATE__, __TIME__);
    Serial.println(logBuffer);
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    sprintf(logBuffer, "OSCNet server IP: %s", myIP.toString().c_str());
    Serial.println(logBuffer);

    Udp.begin(OSCPORT);
    sprintf(logBuffer, "OSC Listening on port %d", OSCPORT);
    Serial.println(logBuffer);
}

void solidColour(OSCMessage &msg)
{
    uint32_t colourAsInt = msg.getInt(0);
    uint8_t r,g,b,a;
    r = (colourAsInt >> 24) & 255;
    g = (colourAsInt >> 16) & 255;
    b = (colourAsInt >> 8) & 255;
    a = colourAsInt & 255;

    sprintf(logBuffer, "Got solid colour request for 0x%2.2X%2.2X%2.2x%2.2X - (%u)", r, g, b, a, colourAsInt);
    Serial.println(logBuffer);
}

void loop()
{
    //OSCBundle bundle;
    OSCMessage msg;
    int size = Udp.parsePacket();

    if (size > 0)
    {
        while (size--)
        {
            msg.fill(Udp.read());
        }
        if (!msg.hasError())
        {
            msg.dispatch("/solid", solidColour);
        }
        else
        {
            error = msg.getError();
            Serial.print("error: ");
            Serial.println(error);
        }
    }
}