#ifndef FLASHINGCOLOURSTATE_H
#define FLASHINGCOLOURSTATE_H

#include <lightingstate.h>

class FlashingColourState: public LightingState {
    private:
        CRGB colour = CRGB(255,0,255);
        int speed=250; //ms for full cycle
    public:
        FlashingColourState(CRGB leds[], int numLeds);

        virtual void setColour(CRGB colour);

        // Inherited
        virtual void update();
};

#endif