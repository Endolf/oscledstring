#include <Arduino.h>
#include "main.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <FastLED.h>

static const char buildInfoLogString[] = "Build data: %s, %s %s";

const char ssid[] = "OSCNet";
const char password[] = "oscnet1324";

char logBuffer[256];

WiFiUDP Udp;
OSCErrorCode error;
CRGB leds[NUM_LEDS];

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

    FastLED.addLeds<LED_TYPE,LED_DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    FastLED.showColor(CRGB(0,0,255));
    fadeToBlackBy(leds, NUM_LEDS, 20);
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

    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
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

    FastLED.show();
}