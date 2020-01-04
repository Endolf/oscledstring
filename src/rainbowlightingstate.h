#ifndef RAINBOWLIGHTINGSTATE_H
#define RAINBOWLIGHTINGSTATE_H

#include <lightingstate.h>

class RainbowLightingState : public LightingState {
    public:
        RainbowLightingState(CRGB leds[], int numLeds);

        // Inherited
        virtual void update();
    private:
        byte hue;
};

#endif