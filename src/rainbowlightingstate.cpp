#include "rainbowlightingstate.h"

RainbowLightingState::RainbowLightingState(CRGB leds[], int numLeds) {
    this->leds = leds;
    this->numLeds = numLeds;
    this->hue=0;
};

void RainbowLightingState::update()
{
    fill_rainbow(leds,numLeds,hue);
    hue--;
};
