#include <Arduino.h>
#include "main.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <FastLED.h>
#include <lightingstate.h>
#include <solidcolourstate.h>

static const char buildInfoLogString[] = "Build data: %s, %s %s";

const char ssid[] = "OSCNet";
const char password[] = "oscnet1324";

char logBuffer[256];

WiFiUDP Udp;
OSCErrorCode error;
CRGB leds[NUM_LEDS];
SolidColourState scs;

LightingState* currentLightingState;

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

    scs.setColour(CRGB(0,64,0));
    currentLightingState = &scs;
}

void solidColour(OSCMessage &msg)
{
    if(msg.isInt(0))
    {
        uint32_t colourAsInt = msg.getInt(0);
        uint8_t r,g,b;
        r = (colourAsInt >> 24) & 255;
        g = (colourAsInt >> 16) & 255;
        b = (colourAsInt >> 8) & 255;

        sprintf(logBuffer, "Got solid colour request for 0x%2.2X%2.2X%2.2X - (%u)", r, g, b, colourAsInt);
        Serial.println(logBuffer);

        scs.setColour(CRGB(colourAsInt));
        currentLightingState = &scs;
    } else {
        Serial.println("Solid colour called but arg 0 was not an int");
    }
}

void solidColourRed(OSCMessage &msg)
{
    if(msg.isFloat(0))
    {
        uint8_t r = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got solid colour red request for 0x%2.2X", r);
        Serial.println(logBuffer);

        scs.setRed(r);
        currentLightingState = &scs;
    } else {
        Serial.println("Solid colour red called but arg 0 was not a float");
    }
}

void solidColourGreen(OSCMessage &msg)
{
    if(msg.isFloat(0))
    {
        uint8_t g = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got solid colour green request for 0x%2.2X", g);
        Serial.println(logBuffer);

        scs.setGreen(g);
        currentLightingState = &scs;
    } else {
        Serial.println("Solid colour green called but arg 0 was not a float");
    }
}

void solidColourBlue(OSCMessage &msg)
{
    if(msg.isFloat(0))
    {
        uint8_t b = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got solid colour blue request for 0x%2.2X", b);
        Serial.println(logBuffer);

        scs.setBlue(b);
        currentLightingState = &scs;
    } else {
        Serial.println("Solid colour blue called but arg 0 was not a float");
    }
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
            msg.dispatch("/*/solidColour", solidColour);
            msg.dispatch("/*/solidColourRed", solidColourRed);
            msg.dispatch("/*/solidColourGreen", solidColourGreen);
            msg.dispatch("/*/solidColourBlue", solidColourBlue);
        }
        else
        {
            error = msg.getError();
            Serial.print("error: ");
            Serial.println(error);
        }
    }

    EVERY_N_MILLISECONDS(1000/FRAMES_PER_SECOND) {
        currentLightingState->update(leds, NUM_LEDS);
        FastLED.show();
    }
}