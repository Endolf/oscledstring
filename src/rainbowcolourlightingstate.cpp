#include "rainbowcolourlightingstate.h"

RainbowColourLightingState::RainbowColourLightingState(CRGB leds[], int numLeds) {
    this->leds = leds;
    this->numLeds = numLeds;
    this->hue=0;
};

void RainbowColourLightingState::update()
{
    fill_solid(leds,numLeds,CHSV(hue,255,192));
    hue = (millis()/millisPerHueStep)%256;
};
