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
    for (int i = 0; i < numDots; i++)
    {
        // leds[beatsin16(15, 0, numLeds - 1,0,(65536/numDots)*i)] |= CHSV(dothue, 200, 255);
        leds[beatsin16(i + (numDots-1), 0, numLeds - 1)] |= CHSV(dothue, 200, 255);
        dothue += 256/numDots;
    }
};
