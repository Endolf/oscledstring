#ifndef FIRELIGHTINGSTATE_H
#define FIRELIGHTINGSTATE_H

#include <lightingstate.h>

class FireLightingState : public LightingState {
    public:
        FireLightingState(CRGB leds[], int numLeds);

        // Inherited
        virtual void update();
    private:
        static const uint8_t cooldown = 55;
        static const uint8_t warming = 120;
        byte* heat;
};

#endif