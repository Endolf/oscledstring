#ifndef SINELONLIGHTINGSTATE_H
#define SINELONLIGHTINGSTATE_H

#include <lightingstate.h>

class SinelonLightingState : public LightingState {
    public:
        SinelonLightingState(CRGB leds[], int numLeds);

        // Inherited
        virtual void update();
    private:
        byte hue;
};

#endif