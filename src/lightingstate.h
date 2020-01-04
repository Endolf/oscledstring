#ifndef LIGHTINGSTATE_H
#define LIGHTINGSTATE_H

//Disable annoying compile "warnings"
#define FASTLED_INTERNAL

#include <FastLED.h>

class LightingState {
    public:
        virtual void update(CRGB leds[], int numLeds) = 0;
};

#endif