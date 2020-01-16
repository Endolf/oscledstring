#include "rainbowflashlightingstate.h"

RainbowFlashLightingState::RainbowFlashLightingState(CRGB leds[], int numLeds) {
    this->numLeds = numLeds;
    this->leds = leds;
    this->hue=0;
};

void RainbowFlashLightingState::update() {
    bool halfTime = (millis()/speed)%2==0;
    bool eighthTime = (millis()/(speed/8))%2==0;

    fill_rainbow(leds,numLeds,hue);
    hue--;

    int quater = numLeds/4;
    if(halfTime) {
        fill_solid(leds+(2*quater),quater*2,CRGB::Black);
        if(!eighthTime) {
            fill_solid(leds,quater,CRGB::Black);
        }
    } else {
        fill_solid(leds,quater*2,CRGB::Black);
        if(!eighthTime) {
            fill_solid(leds+(3*quater),quater,CRGB::Black);
        }
    }
};
