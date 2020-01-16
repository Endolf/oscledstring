#ifndef RAINBOWFLASHINGLIGHTINGSTATE_H
#define RAINBOWFLASHINGLIGHTINGSTATE_H

#include <lightingstate.h>

class RainbowFlashLightingState: public LightingState {
    private:
        int speed=500; //ms for full cycle
        byte hue;
    public:
        RainbowFlashLightingState(CRGB leds[], int numLeds);

        // Inherited
        virtual void update();
};

#endif