#ifndef LIGHTINGSTATE_H
#define LIGHTINGSTATE_H

//Disable annoying compile "warnings"
#define FASTLED_INTERNAL

#include <FastLED.h>

class LightingState {
    public:
        virtual void update() = 0;
    protected:
        CRGB* leds;
        int numLeds;
};

#endif