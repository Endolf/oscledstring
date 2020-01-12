#include "flashingcolourstate.h"

FlashingColourState::FlashingColourState(CRGB leds[], int numLeds) {
    this->numLeds = numLeds;
    this->leds = leds;
};

void FlashingColourState::setColour(CRGB colour) {
    this->colour=colour;
};

void FlashingColourState::setRed(uint8_t red) {
    this->colour[0] = red;
};
void FlashingColourState::setGreen(uint8_t green) {
    this->colour[1] = green;
};
void FlashingColourState::setBlue(uint8_t blue) {
    this->colour[2] = blue;
};

void FlashingColourState::update() {
    bool halfTime = (millis()/speed)%2==0;
    bool eightTime = (millis()/(speed/4))%2==0;
    fill_solid(leds,numLeds,CRGB::Black);
    int half = numLeds/2;
    int quater = numLeds/4;
    if(halfTime) {
        fill_solid(leds+quater,quater,colour);

    } else {
        fill_solid(leds+half,quater,colour);

    }
    if(eightTime) {
        fill_solid(leds+(quater*3),quater,colour);
        fill_solid(leds,quater,colour);
    }
};
