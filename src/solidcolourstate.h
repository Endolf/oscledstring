#ifndef SOLIDCOLOURSTATE_H
#define SOLIDCOLOURSTATE_H

#include <lightingstate.h>

class SolidColourState: public LightingState {
    private:
        CRGB colour = CRGB(0,0,0);
    public:
        virtual void setColour(CRGB colour);
        virtual void setRed(uint8_t red);
        virtual void setGreen(uint8_t green);
        virtual void setBlue(uint8_t blue);

        // Inherited
        virtual void update(CRGB leds[], int numLeds);
};

#endif