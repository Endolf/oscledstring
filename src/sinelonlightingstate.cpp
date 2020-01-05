#include "sinelonlightingstate.h"

SinelonLightingState::SinelonLightingState(CRGB leds[], int numLeds)
{
    this->leds = leds;
    this->numLeds = numLeds;
    this->hue = 0;
};

void SinelonLightingState::update()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, numLeds, 20);
  int pos = beatsin16( 13, 0, numLeds-1 );
  leds[pos] += CHSV( hue, 255, 192);
  hue++;
};
