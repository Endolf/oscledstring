#include "firelightingstate.h"

FireLightingState::FireLightingState(CRGB leds[], int numLeds) {
    this->leds = leds;
    this->numLeds = numLeds;
    heat = new byte[numLeds];

    for(int i=0;i<numLeds;i++) {
        heat[i] = 0;
    }
};

void FireLightingState::update()
{
    for( int i = 0; i < numLeds; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooldown * 10) / numLeds) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= numLeds - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < warming ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Convert to colour
    for (int j = 0; j < numLeds; j++)
    {
        CRGB color = HeatColor(heat[j]);
        leds[j] = color;
    }
};
