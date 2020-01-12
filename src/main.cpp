#include <Arduino.h>
#include "main.h"
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <FastLED.h>
#include "lightingstate.h"
#include "solidcolourstate.h"
#include "flashingcolourstate.h"
#include "firelightingstate.h"
#include "rainbowlightingstate.h"
#include "jugglelightingstate.h"
#include "sinelonlightingstate.h"
#include "rainbowcolourlightingstate.h"

static const char buildInfoLogString[] = "Build data: %s, %s %s";

const char ssid[] = "OSCNet";
const char password[] = "oscnet1324";

char logBuffer[256];

uint8_t brightness = 75;

WiFiUDP Udp;
OSCErrorCode error;
CRGB leds[NUM_LEDS];

SolidColourState scs(leds, NUM_LEDS);
FlashingColourState fcs(leds, NUM_LEDS);
FireLightingState fls(leds, NUM_LEDS);
RainbowLightingState rls(leds, NUM_LEDS);
JuggleLightingState jls(leds, NUM_LEDS);
SinelonLightingState sls(leds, NUM_LEDS);
RainbowColourLightingState rcls(leds, NUM_LEDS);

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
    FastLED.setBrightness(brightness);

    currentLightingState = &rcls;
}

void solidColour(OSCMessage &msg)
{
    if(msg.isInt(0))
    {
        uint32_t colourAsInt = msg.getInt(0);

        sprintf(logBuffer, "Got solid colour request for 0x%6.6X - (%u)", colourAsInt, colourAsInt);
        Serial.println(logBuffer);

        scs.setColour(CRGB(colourAsInt));
        currentLightingState = &scs;
    } else {
        Serial.println("Solid colour called but arg 0 was not an int");
        currentLightingState = &scs;
    }
}

void adjustRed(OSCMessage &msg)
{
    if(msg.isFloat(0))
    {
        uint8_t r = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got adjust red request for 0x%2.2X", r);
        Serial.println(logBuffer);

        scs.setRed(r);
        fcs.setRed(r);
    } else {
        Serial.println("Adjust red called but arg 0 was not a float");
    }
}

void adjustGreen(OSCMessage &msg)
{
    if(msg.isFloat(0))
    {
        uint8_t g = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got adjust green request for 0x%2.2X", g);
        Serial.println(logBuffer);

        scs.setGreen(g);
        fcs.setGreen(g);
    } else {
        Serial.println("Adjust green called but arg 0 was not a float");
    }
}

void adjustBlue(OSCMessage &msg)
{
    if(msg.isFloat(0))
    {
        uint8_t b = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got adjust blue request for 0x%2.2X", b);
        Serial.println(logBuffer);

        scs.setBlue(b);
        fcs.setBlue(b);
    } else {
        Serial.println("Adjust blue called but arg 0 was not a float");
    }
}

void setFireState(OSCMessage &msg) {
    currentLightingState = &fls;
    FastLED.setBrightness(25);
    Serial.println("Got request for fire");
}

void setRainbowState(OSCMessage &msg) {
    currentLightingState = &rls;
    FastLED.setBrightness(25);
    Serial.println("Got request for rainbow");
}

void setJuggleState(OSCMessage &msg) {
    currentLightingState = &jls;
    FastLED.setBrightness(75);
    Serial.println("Got request for juggle");
}

void setSinelonState(OSCMessage &msg) {
    currentLightingState = &sls;
    FastLED.setBrightness(65);
    Serial.println("Got request for sinelon");
}

void setBrightness(OSCMessage &msg) {
    if(msg.isFloat(0))
    {
        uint8_t b = 255 * msg.getFloat(0);

        sprintf(logBuffer, "Got brightness request for 0x%2.2X (%u)", b, b);
        Serial.println(logBuffer);

        FastLED.setBrightness(b);
    } else {
        Serial.println("Set brightness called but arg 0 was not a float");
    }
}

void flashingColour(OSCMessage &msg)
{
    if(msg.isInt(0))
    {
        uint32_t colourAsInt = msg.getInt(0);

        sprintf(logBuffer, "Got flashing colour request for 0x%6.6X - (%u)", colourAsInt, colourAsInt);
        Serial.println(logBuffer);

        fcs.setColour(CRGB(colourAsInt));
        currentLightingState = &fcs;
    } else {
        Serial.println("Flashing colour called but arg 0 was not an int");
        currentLightingState = &fcs;
    }
}

void setRainblowColourState(OSCMessage &msg) {
    currentLightingState = &rcls;
    FastLED.setBrightness(25);
    Serial.println("Got request for rainbow colour");
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
            msg.dispatch("/*/adjustRed", adjustRed);
            msg.dispatch("/*/adjustGreen", adjustGreen);
            msg.dispatch("/*/adjustBlue", adjustBlue);
            msg.dispatch("/*/flashingColour", flashingColour);
            msg.dispatch("/*/fire", setFireState);
            msg.dispatch("/*/rainbow", setRainbowState);
            msg.dispatch("/*/juggle", setJuggleState);
            msg.dispatch("/*/sinelon", setSinelonState);
            msg.dispatch("/*/brightness", setBrightness);
            msg.dispatch("/*/solidRainbow", setRainblowColourState);
        }
        else
        {
            error = msg.getError();
            Serial.print("error: ");
            Serial.println(error);
        }
    }

    EVERY_N_MILLISECONDS(1000/FRAMES_PER_SECOND) {
        currentLightingState->update();
        FastLED.show();
    }
}