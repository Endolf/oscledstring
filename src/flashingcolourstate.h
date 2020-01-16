#ifndef FLASHINGCOLOURSTATE_H
#define FLASHINGCOLOURSTATE_H

#include <lightingstate.h>

class FlashingColourState: public LightingState {
    private:
        CRGB colour = CRGB(0,0,0);
        int speed=500; //ms for full cycle
    public:
        FlashingColourState(CRGB leds[], int numLeds);

        virtual void setColour(CRGB colour);
        virtual void setRed(uint8_t r);
        virtual void setGreen(uint8_t r);
        virtual void setBlue(uint8_t r);

        // Inherited
        virtual void update();
};

#endif