#ifndef RAINBOWCOLOURLIGHTINGSTATE_H
#define RAINBOWCOLOURLIGHTINGSTATE_H

#include <lightingstate.h>

class RainbowColourLightingState : public LightingState {
    public:
        RainbowColourLightingState(CRGB leds[], int numLeds);

        // Inherited
        virtual void update();
    private:
        byte hue;
        //hz
        int freq = 10;
        int millisPerHueStep = 4*freq;
};

#endif