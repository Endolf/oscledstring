#include "jugglelightingstate.h"

JuggleLightingState::JuggleLightingState(CRGB leds[], int numLeds)
{
    this->leds = leds;
    this->numLeds = numLeds;
};

void JuggleLightingState::update()
{
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, numLeds, 20);
    byte dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        leds[beatsin16(i + 7, 0, numLeds - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
};
