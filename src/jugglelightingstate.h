#ifndef JUGGLELIGHTINGSTATE_H
#define JUGGLELIGHTINGSTATE_H

#include <lightingstate.h>

class JuggleLightingState : public LightingState {
    public:
        JuggleLightingState(CRGB leds[], int numLeds);

        // Inherited
        virtual void update();
    private:
        static const byte numDots = 9;
};

#endif